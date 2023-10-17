pythonPath=`where python | grep "Scripts"`
echo "python执行路径:"${pythonPath}
pythonFiles=`find ./ -name *.py`
for file in ${pythonFiles[*]}; 
do
	echo "文件名:"${file}
	compeltePath=$(pwd)${file:1}
	echo "文件完整路径:"${compeltePath}
	$pythonPath ${file}
done

