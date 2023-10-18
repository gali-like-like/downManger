pythonPath=`where python | grep "Scripts"`
echo "python执行路径:"${pythonPath}
pythonFiles=`find ./ -name "*.py"`
echo "查找到的python文件:"${pythonFiles[*]}
for file in ${pythonFiles[*]}; 
do
	#echo ${file}
	compeltePath=$(pwd)${file:1}
 	echo "当前文件完整路径:"${compeltePath}
	$pythonPath ${file} 
done

