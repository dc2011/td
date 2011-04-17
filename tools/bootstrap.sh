TDREPO=https://github.com/dc2011/td.git
BRANCH=master

if [[ `whoami` != 'root' ]]; then
    echo "You must run this as root!"
    exit 1
fi

cd /root/Desktop
git clone $TDREPO ./TowerDefense
cd ./TowerDefense
git checkout $BRANCH

cd ./tools
. deps.sh
. extrafiles.sh
cd ..
qmake-qt4
make -j4
