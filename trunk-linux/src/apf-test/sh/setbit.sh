setbit()
 {
     PORT=$1
     NB=$2
     VAL=$3
     cat $PORT | sed "s/[0-1]\([0-1]\{$NB\}\)$/$VAL\1/" > $PORT
 }

