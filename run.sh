
make;

echo running....;
./Q1 -t 5 -l 6 -n 5 fif > q.log 2> q.err & ./U1 -t 5 fif > u.log 2> u.err;
