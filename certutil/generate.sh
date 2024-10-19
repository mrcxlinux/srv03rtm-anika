#!/bin/bash
set -xe

initdir="$(pwd)"
configdir="$initdir/config"
sourcedir="$initdir/source"

installdir="$initdir/srv03rtm.certs"
rm -rf "$installdir"
mkdir -p "$installdir"

isubdir() {
  local path="$installdir/$1"
  [ -d "$path" ] || mkdir -p "$path" || return $?
  echo "$path"
}

testrootcert="$(isubdir 'tools')/testroot.cer"
testpcacert="$(isubdir 'tools')/testpca.cer"
vbl03cacert="$(isubdir 'tools')/vbl03ca.cer"
drivercert="$(isubdir 'tools')/driver.pfx"

(certdir="$(isubdir '_gencerts')"
cd "$certdir"

mkdir 'testroot.db.certs'
touch 'testroot.db.index'
echo '4831793303313605' > 'testroot.db.serial'
openssl req -x509 -md5 -newkey rsa:1536 -nodes -config "$configdir/testroot.conf" -keyout 'testroot.key' -out 'testroot.pem' -days 73000
openssl x509 -outform der -in 'testroot.pem' -out "$testrootcert"

mkdir 'testpca.db.certs'
touch 'testpca.db.index'
echo '3921298631018096' > 'testpca.db.serial'
openssl req -new -newkey rsa:1536 -nodes -config "$configdir/testpca.conf" -keyout 'testpca.key' -out 'testpca.csr'
openssl ca -batch -config "$configdir/testroot.conf" -in 'testpca.csr' -out 'testpca.pem'
openssl x509 -outform der -in 'testpca.pem' -out "$testpcacert"

mkdir 'vbl03ca.db.certs'
touch 'vbl03ca.db.index'
echo '2208785574689461' > 'vbl03ca.db.serial'
openssl req -new -newkey rsa:2048 -nodes -config "$configdir/vbl03ca.conf" -keyout 'vbl03ca.key' -out 'vbl03ca.csr'
openssl ca -batch -config "$configdir/testpca.conf" -in 'vbl03ca.csr' -out 'vbl03ca.pem'
openssl x509 -outform der -in 'vbl03ca.pem' -out "$vbl03cacert"

openssl req -new -newkey rsa:1024 -nodes -config "$configdir/driver.conf" -keyout 'driver.key' -out 'driver.csr'
openssl ca -batch -config "$configdir/vbl03ca.conf" -in 'driver.csr' -out 'driver.pem'
openssl pkcs12 -export -nodes -password pass: -in 'driver.pem' -inkey 'driver.key' -certfile 'testroot.pem' -certfile 'vbl03ca.pem' -out "$drivercert"

cp "$testrootcert" "$(isubdir 'mergedcomponents/setupinfs')/testroot.cer"
cd "$installdir"
rm -rf "$certdir")

for f in "$initdir/source/"*; do 
  path="$(sed 's,-,/,g' <<< ${f##*/})"
  cp "$f" "$(isubdir "${path%/*}")/${path##*/}"
done

certsha1() {
  local sha1
  if [ "${1##*.}" = 'cer' ]; then
    sha1="$(openssl x509 -inform der -in "$1" -noout -fingerprint -sha1)"
  elif [ "${1##*.}" = 'pfx' ]; then
    sha1="$(openssl pkcs12 -in "$1" -nodes -passin pass: |
    openssl x509 -noout -fingerprint -sha1)"
  else
    return 1
  fi
  [ "$?" = 0 ] || return 1
  sed 's/:/ /g' <<< "${sha1##*=}"
}

join4() {
  local hash="$(printf '%s%s%s%s ' "$@")"
  echo "${hash:0: -1}"
}

joinba() {
  local array="$(printf '0x%s, ' "$@")"
  echo "${array:0: -2}"
}

certpk() {
  openssl x509 -inform der -in "$1" -noout -pubkey |
  grep -Fv -- ----- | base64 -d | xxd -p -c 1 | xargs
}

pksha1() {
  local hash="$(printf '%s' "$@" | xxd -p -r | sha1sum)"
  hash="$(sed 's/../& /g' <<< "${hash%% *}")"
  echo "${hash:0: -1}"
}

testrootsha1="$(certsha1 "$testrootcert")"
testpcasha1="$(certsha1 "$testpcacert")"
driversha1="$(certsha1 "$drivercert")"
testrootpk="$(certpk "$testrootcert")"
testrootpksha1="$(pksha1 "$testrootpk")"

perl -0777 -pe "s/0x8E, 0xFF, [\s\S]*, 0xDC, 0x53/$(joinba $testrootpksha1)/"-i "$installdir/ds/security/cryptoapi/pki/certstor/policy.cpp"

sed -e "s/0xA4, 0xCA, .*, 0xC7, 0xAB/$(joinba $testrootsha1)/" -i "$installdir/base/win32/fusion/sxs/strongname.cpp" -i "$installdir/base/ntsetup/syssetup/crypto.c"
perl -0777 -pe "s/(?<=BYTE rgbTestRoot0_PubKeyInfo\[\]= \{)[^}]*/\r\n$(joinba $testrootpk)\r\n/" -i "$installdir/ds/security/cryptoapi/mincrypt/lib/vercert.cpp"-i "$installdir/ds/win32/ntcrypto/mincrypt/vercert.cpp"

sed -e "s/A4CAECFC.*07B0C7AB/$(printf '%s' $testrootsha1)/" -i "$installdir/ds/win32/ntcrypto/mincrypt/vercert.cpp" -i "$installdir/shell/shell32/defview.cpp" -i "$installdir/windows/core/ntuser/kernel/server.c"

sed -e "s/52871BBC.*06D7A08D/$(join4 $testpcasha1)/" -i "$installdir/tools/checktestpca.cmd"
sed -e "s/A4CAECFC.*07B0C7AB/$(join4 $testrootsha1)/" -i "$installdir/tools/checktestroot.cmd"

sed -e "s/5B8962DC.*2706CDBC/$(printf '%s' $driversha1)/" -i "$installdir/tools/postbuildscripts/crypto.cmd"