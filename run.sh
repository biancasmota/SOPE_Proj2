clear;
make;

echo running....;
./Q1 -t 15 -l 6 -n 15 fif > q.log 2> q.err & ./U1 -t 20 fif > u.log 2> u.err;
