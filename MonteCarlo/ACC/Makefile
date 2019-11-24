acc:
	pgc++ -ta=tesla -Minfo=accel monte_pi.cpp -o monte_pi

run:
	srun -p cisc372 --gres=gpu:1 ./monte_pi

clean:
	rm monte_pi
