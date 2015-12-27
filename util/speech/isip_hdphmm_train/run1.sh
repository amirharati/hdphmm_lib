#!/bin/sh                                                                       
#PBS -l walltime=4:00:00                                                       
#PBS -N  exp027_run1                                                                   
#PBS -q highmem
       	   
#PBS -A tuc56736                                                               

#PBS -m ae                                                                     

#PBS -M amir.harati@gmail.com       

#PBS -l nodes=1:ppn=8                                                          
#PBS                                                                            
cd $PBS_O_WORKDIR

mkdir $TMPDIR/outputs
mkdir raw_models

export  exp_name="exp028";
export itr=200;
export load="";
export  last_itr=0;
export burnin=150;

OMP_NUM_THREADS=8 \
isip_hdphmm_train.exe  -params_file params.sof -train_file train_zh.db  -itr 200  -init_itr 0  -burn_in 190 -structure_type LEFT_TO_RIGHT -emission_type DPM -kz 10  -output_mode TEXT -hmm_params 10,1,10,1,10,1 -emission_params 20,1,10,1,.1,1000 -raw_model raw_model.text -seeds 113,101,1001,17,23,10001 > out 2>&1


wait

#cp  --preserve=timestamps -rf $TMPDIR/outputs/*  raw_models
