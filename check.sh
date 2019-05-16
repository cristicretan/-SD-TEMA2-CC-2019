#!/usr/bin/env bash


# e1 - 20
# e2 - 15
# e3 - 15
# u - 10
# c - 30
# b - 20
# - adaug memory leakuri

# rm-uri
# mkdiruri
#make clean
#make build

make clean
make build

#nr = numar teste
nr=10

#stval = val pt bonus
sigma=250

input_dir="./tests/inputs/"
ref_dir="./tests/refs/"
ZERO=0
VALGRIND_ARGS="--leak-check=full --track-origins=yes -q --log-file=rezultat_valgrind.txt"

result=0
leaks=false
for entry in `seq $nr`; do	
	qin=${input_dir}queries.in${entry}
	tin=${input_dir}tree.in${entry}
	uin=${input_dir}users.in${entry}
	tref=${ref_dir}tree.out${entry}
	href=${ref_dir}hierarchy.out${entry}
	qref=${ref_dir}queries.out${entry}
	tout=tree.out
	hout=hierarchy.out
	qout=queries.out
	declare -a outs=($tout $hout $qout)
	declare -a refs=($tref $href $qref)
	cp $qin queries.in
	cp $tin tree.in
	cp $uin users.in

	valgrind $VALGRIND_ARGS ./tema2 &> /dev/null
	[ -s rezultat_valgrind.txt ]
   	EXIT_CODE=$?
   	rm rezultat_valgrind.txt
    	if [[ $EXIT_CODE -eq $ZERO ]]
    	then
    	        echo "Memory leaks"
    	        leaks=true
    	else
    	        echo "No memory leaks"
    	fi
 	./tema2
 	python sort_tree.py
 	for i in `seq 3`; do
		toAdd=3
		x=$(($i-1))
		diff "${outs[$x]}" "${refs[$x]}" > /dev/null			

		EXIT_CODE=$?
		if [[ $EXIT_CODE -eq $ZERO ]]
		then
	          		echo "Test $entry - Task $i __________________ PASSED [$toAdd p]"
			result=$((result + toAdd))
		else
			echo "Test $entry - Task $i __________________ FAILED"
	    	fi
	done
done
for entry in `seq 11 15`; do	
	qin=${input_dir}queries.in${entry}
	tin=${input_dir}tree.in${entry}
	uin=${input_dir}users.in${entry}
	tref=${ref_dir}tree.out${entry}
	href=${ref_dir}hierarchy.out${entry}
	qref=${ref_dir}queries.out${entry}
	tout=tree.out
	hout=hierarchy.out
	qout=queries.out
	declare -a outs=($tout $hout $qout)
	declare -a refs=($tref $href $qref)
	cp $qin queries.in
	cp $tin tree.in
	cp $uin users.in

	valgrind $VALGRIND_ARGS ./tema2 &> /dev/null
	[ -s rezultat_valgrind.txt ]
   	EXIT_CODE=$?
   	rm rezultat_valgrind.txt
    	if [[ $EXIT_CODE -eq $ZERO ]]
    	then
    	        echo "Memory leaks"
    	        leaks=true
    	else
    	        echo "No memory leaks"
    	fi
 	./tema2
 	python sort_tree.py
	
	toAdd=4
	ok=true
 	for i in `seq 3`; do
		x=$(($i-1))
		diff "${outs[$x]}" "${refs[$x]}" > /dev/null			

		EXIT_CODE=$?
		if [[ $EXIT_CODE -ne $ZERO ]]
		then
			ok=false
	    fi
	done
	if $ok;	then
        echo "Test $entry - BONUS __________________ PASSED [$toAdd p]"
		result=$((result + toAdd))
	else
		echo "Test $entry - BONUS __________________ FAILED"
    	fi

done
rm queries.in tree.in users.in
rm queries.out tree.out hierarchy.out
make clean

echo "Result = $result"
if $leaks; then
	echo "Memory leaks"
else
	echo "No memory leaks"
fi
