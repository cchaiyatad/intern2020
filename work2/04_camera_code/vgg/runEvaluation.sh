if [ $# -eq 1 ]
    then
        mkdir output
        for imageName in ../JPEGImages/0*.jpg
        do 
            echo $imageName
            NAME=${imageName##*/} 
            NAME=${NAME%.*}
            ./run.sh $imageName $1 > output/$NAME.txt
        done
else
    echo "Usage: ./runEvalutation.sh [threshold]"
fi

