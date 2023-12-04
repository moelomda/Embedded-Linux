#!/bin/bash

user=$(whoami)
hostname=$(hostname)

echo " my username is : $user"
echo " my hostname is : $hostname"

if [ -d "/home/exam_directory" ]  then     // -d checks whether the directory exsts 

	echo " i found your directory "

   if [ -d "/home/exam_directory/" ] then  
          
          echo "the directory contains files "    
 
	   ls -sh "/home/exam_directory/"

     else 
           echo " directory exists but is empty "
	 cd ~
         cd exam_directory
         touch file1.txt
         touch file2.txt
         touch file3.txt	
         
fi  
    
 else   
      
    cd ~
    mkdir exam_directory 
    cd  exam_directory
    touch file1.txt
    touch file2.txt
    touch file3.txt
    
 fi 




      	   
