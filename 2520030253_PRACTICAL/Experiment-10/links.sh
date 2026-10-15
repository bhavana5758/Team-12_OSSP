
#!/bin/bash

echo "Experiment 10: Inodes and Links"

echo "Original file content" > original.txt

ln original.txt hardlink.txt
ln -s original.txt symlink.txt

echo "File details:"
ls -li original.txt hardlink.txt symlink.txt

echo "Hard link content:"
cat hardlink.txt

echo "Symbolic link content:"
cat symlink.txt
