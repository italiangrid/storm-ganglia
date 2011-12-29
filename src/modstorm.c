/*
 Ganglia module to get metrics from the heartbeat.log of StoRM service
 Taken from the line before last of the log file.
 Metrics:
			heapF: Heap free memory in Bytes
<<<<<<< HEAD
			nsync: Number of synchronous requests
=======
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5
			aptp aptg: Number of "Assyncronous Prepare To Put" and ""Assyncronous Prepare To Get"
			sptp sptg: Number of "Syncronous Prepare To Put" and ""Syncronous Prepare To Get"
			err_syn_ptp err_syn_ptg: Number of errors in sptp and sptg, as the difference spt*-spt*ok
			sptpTime sptgTime: Average time to process PTP and PTG requests.

 Author: Mario David ( david@lip.pt )
<<<<<<< HEAD
 Version: 1.0.2-1
=======
 Version: 1.0.1-1
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <gm_metric.h>

<<<<<<< HEAD
#define STRID 6
#define NMETRIC 10
=======
#define NMETRIC 9
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5
#define HBLOG "/var/log/storm/heartbeat.log"

mmodule storm_mon_module;

int hb_val_get (metric_index)
{
<<<<<<< HEAD
	int year= 0, month= 0, day= 0, hour= 0, min= 0, sec= 0, msec= 0, lhour= 0, lmin= 0, lsec= 0, heapF= 0;
	int nsync= 0, aptg= 0, aptp= 0, sptg= 0, sptgok= 0, sptgTime= 0, sptp= 0, sptpok= 0, sptpTime= 0;
	int err_syn_ptp= 0,err_syn_ptg= 0;
	char strn[STRID];
=======
	int year= 0, month= 0, day= 0, hour= 0, min= 0, sec= 0, msec= 0, num= 0, lhour= 0, lmin= 0, lsec= 0, heapF= 0;
	int nsync= 0, aptg= 0, aptp= 0, sptg= 0, sptgok= 0, sptgTime= 0, sptp= 0, sptpok= 0, sptpTime= 0;
	int err_syn_ptp= 0,err_syn_ptg= 0;
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5

	int bytes = 0;
	int nl = 0;
	FILE* f1;

// Jump to line before last, not the last line to be safe
	f1 = fopen (HBLOG,"r");
	while(fseek(f1, --bytes, SEEK_END) == 0)
	{
<<<<<<< HEAD
		if (fgetc(f1) == '\n' && ++nl > 1)
=======
		if (fgetc(f1) == '\n' && ++nl > 2)
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5
		{
			break;
		}
	}

// Format of the hearbeat.log line
//[2011-11-18 16:52:32,737]:  [#..3042 lifetime=50:41.01] Heap Free:457283768 SYNCH [21] ASynch [PTG:20368 PTP:12897] Last:( [#PTG=16 OK=16 M.Dur.=70] [#PTP=0 OK=0 M.Dur.=0] )

<<<<<<< HEAD
	fscanf(f1,"[%d-%d-%d %d:%d:%d,%d]:  [#%s lifetime=%d:%d.%d] Heap Free:%d SYNCH [%d] ASynch [PTG:%d PTP:%d] Last:( [#PTG=%d OK=%d M.Dur.=%d] [#PTP=%d OK=%d M.Dur.=%d] )",
	            &year, &month, &day, &hour, &min, &sec, &msec, strn, &lhour, &lmin, &lsec, &heapF,
=======
	fscanf(f1,"[%d-%d-%d %d:%d:%d,%d]:  [#..%d lifetime=%d:%d.%d] Heap Free:%d SYNCH [%d] ASynch [PTG:%d PTP:%d] Last:( [#PTG=%d OK=%d M.Dur.=%d] [#PTP=%d OK=%d M.Dur.=%d] )",
	            &year, &month, &day, &hour, &min, &sec, &msec, &num, &lhour, &lmin, &lsec, &heapF,
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5
		        &nsync, &aptg, &aptp, &sptg, &sptgok, &sptgTime, &sptp, &sptpok, &sptpTime);
	fclose(f1);

	err_syn_ptg = abs(sptg - sptgok);
	err_syn_ptp = abs(sptp - sptpok);

<<<<<<< HEAD
	int srm_metric[] = {heapF, nsync, aptg, aptp, sptg, err_syn_ptg, sptgTime, sptp, err_syn_ptp, sptpTime};
=======
	int srm_metric[] = {heapF, aptg, aptp, sptg, err_syn_ptg, sptgTime, sptp, err_syn_ptp, sptpTime};
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5

	return srm_metric[metric_index];
}


static int storm_mon_module_init ( apr_pool_t *p )
{
	int i;

	libmetrics_init();

	for (i = 0; storm_mon_module.metrics_info[i].name != NULL; i++)
	{
		 MMETRIC_INIT_METADATA (&(storm_mon_module.metrics_info[i]),p);
		 MMETRIC_ADD_METADATA  (&(storm_mon_module.metrics_info[i]),MGROUP,"srm");
	}
	return 0;
}

static g_val_t storm_mon_module_handler ( int metric_index )
{
    g_val_t val;

	val.int32 = hb_val_get(metric_index);
	return val;
}


static void storm_mon_module_cleanup ( void )
{
}

static Ganglia_25metric storm_mon_module_info[] =
{
    {0, "mem_heap_free", 60, GANGLIA_VALUE_INT, "Bytes", "both",     "%d", UDP_HEADER_SIZE+8, "Memory heap free in Bytes"},
<<<<<<< HEAD
    {0, "nsync_req",     60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Number of synchronous requests"},
    {0, "asyn_ptg",      60, GANGLIA_VALUE_INT, "Num",   "positive", "%d", UDP_HEADER_SIZE+8, "Assynchronous PTP requests"},
    {0, "asyn_ptp",      60, GANGLIA_VALUE_INT, "Num",   "positive", "%d", UDP_HEADER_SIZE+8, "Assynchronous PTG requests"},
    {0, "syn_ptg",       60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Synchronous PTG requests"},
    {0, "err_syn_ptg",   60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Num Errors Synchronous PTG requests"},
    {0, "time_syn_ptg",  60, GANGLIA_VALUE_INT, "ms",    "both",     "%d", UDP_HEADER_SIZE+8, "Average Time Synchronous PTG requests in ms"},
    {0, "syn_ptp",       60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Synchronous PTP requests"},
    {0, "err_syn_ptp",   60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Num Errors Synchronous PTP requests"},
    {0, "time_syn_ptp",  60, GANGLIA_VALUE_INT, "ms",    "both",     "%d", UDP_HEADER_SIZE+8, "Average Time Synchronous PTP requests in ms"},
=======
    {0, "asyn_ptg",      60, GANGLIA_VALUE_INT, "Num",   "positive", "%d", UDP_HEADER_SIZE+8, "Assyncronous PTP requests"},
    {0, "asyn_ptp",      60, GANGLIA_VALUE_INT, "Num",   "positive", "%d", UDP_HEADER_SIZE+8, "Assyncronous PTG requests"},
    {0, "syn_ptp",       60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Syncronous PTP requests"},
    {0, "err_syn_ptp",   60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Num Errors Syncronous PTP requests"},
    {0, "time_syn_ptp",  60, GANGLIA_VALUE_INT, "ms",    "both",     "%d", UDP_HEADER_SIZE+8, "Average Time Syncronous PTP requests in ms"},
    {0, "syn_ptg",       60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Syncronous PTG requests"},
    {0, "err_syn_ptg",   60, GANGLIA_VALUE_INT, "Num",   "both",     "%d", UDP_HEADER_SIZE+8, "Num Errors Syncronous PTG requests"},
    {0, "time_syn_ptg",  60, GANGLIA_VALUE_INT, "ms",    "both",     "%d", UDP_HEADER_SIZE+8, "Average Time Syncronous PTG requests in ms"},
>>>>>>> e2d54141a07b133103947f25590afbe7d7aa23f5
    {0, NULL}
};

mmodule storm_mon_module =
{
    STD_MMODULE_STUFF,
    storm_mon_module_init,
    storm_mon_module_cleanup,
    storm_mon_module_info,
    storm_mon_module_handler,
};
