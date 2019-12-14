for i in $(find ex -type f)
do
	./parser $i
	if [ $? -ne 0 ]
	then
		if [ "$i" == "ex/err1.kal" ]
		then
			continue
		fi
		printf "Failed to execute %s\n" "$i"
		echo "########################"
		cat -n "$i"
		break
	fi
done
