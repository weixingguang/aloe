/* 
 * Copyright (c) 2012, Ismael Gomez-Miguelez <ismael.gomez@tsc.upc.edu>.
 * This file is part of ALOE++ (http://flexnets.upc.edu/)
 * 
 * ALOE++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ALOE++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with ALOE++.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef rtdal_PROCESS_H
#define rtdal_PROCESS_H

#include "str.h"
#include "rtdal_types.h"
#include "rtdal.h"

struct _rtdal_process_t {
	int pid;

	void *pipeline;
	void *arg;
	struct rtdal_process_attr attributes;

	void* dl_handle;
	int (*run_point)(void*);
	void (*abort_point)(void*);
	int is_running;
	int runnable;
	rtdal_processerrors_t finish_code;
	strdef(error_msg);
	/* pointer to the next process in the pipeline spscq */
	struct _rtdal_process_t *next;
};
typedef struct _rtdal_process_t rtdal_process_t;

int rtdal_process_launch(rtdal_process_t *proc);

#endif
