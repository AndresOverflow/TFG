BEGIN {
    print "************     Begin Study     **********\n"
    number_of_exe = 0
    sum = 0
    average = 0
    dif = 0
    variance = 0
    std_dev = 0
}

{
    if ($1 == "HSPR1" && $2 == "480" && $3 == "8000") {
        number_of_exe = NF - 5
        for (i = 6; i < NF + 1; i++) {
            sum += $i
            print $i
        }

        average = (sum/number_of_exe)
        print "============================"

        for (i = 6; i < NF + 1; i++) {

            diff = ( ( ($i - average) * ($i - average) ) / (NF - 5) )
            print diff
            variance = variance + diff
        }
        
        std_dev = sqrt(variance)
    }
}
END {
    print "Number of executions", (number_of_exe)
    print "Mean is equal to", (average) 
    print "Variance is ", variance
    print "Standar deviation is ", std_dev

    print sum

    print "************     End Study     **********\n"
}
