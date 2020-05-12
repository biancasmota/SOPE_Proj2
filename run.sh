clear;
make;

echo running....;
./U1 -t 20 fif > u.log 2> u.err & ./Q1 -t 30 fif > q.log 2> q.err;