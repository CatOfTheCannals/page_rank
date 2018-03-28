# TODO include universal installer script for wget https://www.xkcd.com/1654/ # or should I be using `curl`, instead?

# this script is meant to be run from the repo's root folder, like this: `./scripts/dl-files.sh`
# it gets you this practical work's presentation and instructions' pdf, and its' test cases

wget --force-html -i http://www-2.dc.uba.ar/materias/metnum/dnload/2018_C1/tp1/tp1.html
unzip tests_tp1.zip
rm -rf __MACOSX
rm tests_tp1.zip
rm tp1.html
rm tests_tp1/.DS_Store

