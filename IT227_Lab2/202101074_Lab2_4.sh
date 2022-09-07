#!/bin/bash
## Jenil_Patel_202101074
## Sort and Delete the duplicate lines from the text file

file_=$1
if [[ ! $1 ]];then
	file_="./Test_Folder/test.txt"
fi
chmod u+rwx $file_
function deleteDuplicates() {	# Need to make another temp file as can't assign result to the our target file itself.
	touch tempFile.txt && chmod u+rwx tempFile.txt
	cp $file_ tempFile.txt
	rm $file_
	sort -u tempFile.txt > ${file_}
	chmod u+rwx $file_
	rm tempFile.txt
}
deleteDuplicates
## Sorted and duplicate lines deleted and Display the file
cat ${file_}
