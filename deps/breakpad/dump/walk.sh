if [ ! -f *.dmp ];then
	echo "\033[1;36m No dump produced. \033[0m"
    exit 1
fi

rm -f ./symbols
./dump_syms -a x86_64 usnit_app.app.dSYM > usnit_app.sym 
sum=`head -n1 usnit_app.sym | awk '{print $4}'`
echo "\033[1;36m $sum \033[0m"

mkdir -p symbols/usnit_app/$sum
mv usnit_app.sym symbols/usnit_app/$sum

echo "\033[1;36m begin walk \033[0m"
./minidump_stackwalk ./*.dmp symbols > crashed.log  
echo "\033[1;36m check crashed.log  \033[0m"
