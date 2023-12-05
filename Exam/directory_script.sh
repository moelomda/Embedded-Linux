#!/bin/bash

user=$(whoami)
hostname=$(hostname)
cd $HOME
echo " my username is : $user"
echo " my hostname is : $hostname"

if [ -d "exam_directory" ]
     then    

                            
	echo " i found your directory "

   if [ -d "exam_directory" ]
   
       then 
       
          
       echo "the directory contains files "    
 
	   ls -sh "exam_directory"
     else 
         echo " directory exists but is empty "
	     cd $HOME
         cd exam_directory
         touch file1.txt
         touch file2.txt
         touch file3.txt		
fi  
    
 else  
    echo "derictory not exist asln"
    cd $HOME
    mkdir exam_directory 
    cd  exam_directory
    touch file1.txt
    touch file2.txt
    touch file3.txt
    
 fi
