#! /bin/sh
committime=$(date);

git add ./*;
echo "aaa";
git commit -m "$committime";
echo "aaa";

git push origin master;
echo "aaa";

