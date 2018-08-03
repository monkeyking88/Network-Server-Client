#echo "Question 1 and 3:" > result.csv
#echo "--------------------------------------------------------------------------------" >> result.csv
#echo "N,A,,Throughput, Average delay" >> result.csv
#echo "" >> result.csv
#echo "10000  20 5 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  40 5 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  60 5 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  80 5 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 100 5 1 1500 0" | ./simulation.out >> result.csv
#echo "" >> result.csv
#echo "10000  20 6 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  40 6 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  60 6 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  80 6 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 100 6 1 1500 0" | ./simulation.out >> result.csv
#echo "" >> result.csv
#echo "10000  20 7 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  40 7 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  60 7 1 1500 0" | ./simulation.out >> result.csv
#echo "10000  80 7 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 100 7 1 1500 0" | ./simulation.out >> result.csv

#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv

#echo "Question 2 and 4:" >> result.csv
#echo "--------------------------------------------------------------------------------" >> result.csv
#echo "N,A,,Throughput, Average delay" >> result.csv
#echo "" >> result.csv
#echo "10000 20  4 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 20  8 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 20 12 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 20 16 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 20 20 1 1500 0" | ./simulation.out >> result.csv
#echo "" >> result.csv
#echo "10000 30  4 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30  8 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30 12 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30 16 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30 20 1 1500 0" | ./simulation.out >> result.csv
#echo "" >> result.csv
#echo "10000 40  4 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 40  8 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 40 12 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 40 16 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 40 20 1 1500 0" | ./simulation.out >> result.csv

#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv

#echo "Question 5 (Non-Persistent):" >> result.csv
#echo "--------------------------------------------------------------------------------" >> result.csv
#echo "N,A,,Throughput, Average delay" >> result.csv
#echo "" >> result.csv
#echo "10000 30  6 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30  7 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30  8 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30  9 1 1500 0" | ./simulation.out >> result.csv
#echo "10000 30 10 1 1500 0" | ./simulation.out >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv
#echo "" >> result.csv

echo "Question 5 (p-Persistent):" >> result.csv
echo "--------------------------------------------------------------------------------" >> result.csv
echo "N,A,,Throughput, Average delay" >> result.csv
echo "" >> result.csv
echo "10000 30 10 1 1500 1" | ./simulation.out >> result.csv
echo "10000 30 10 1 1500 10" | ./simulation.out >> result.csv
echo "10000 30 10 1 1500 30" | ./simulation.out >> result.csv
echo "10000 30 10 1 1500 60" | ./simulation.out >> result.csv
echo "10000 30 10 1 1500 100" | ./simulation.out >> result.csv
