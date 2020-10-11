BEGIN {
    print "************     Begin Study     **********\n"
    number_of_exe = 0
}

{
    if ($1 == "STATIC" && $3 == "30") {
        number_of_exe = NF - 5
        for (i = 6; i < NF + 1; i++) {
            sum += $i
            print $i
        }
    }
}
END {
    print "Number of executions", (number_of_exe)
    print "Medium is equal to", (sum/number_of_exe) 
    print sum

    print "************     End Study     **********\n"
}
