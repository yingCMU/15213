unsigned long set_id, tag_id;
	set_id = (set_mask & mem_addr) >> b;
	tag_id = tag_mask & mem_addr;
	
	Set *set = sets + set_id;
	//should be a pointer
	Line *line;
	printf("! here %ls",set->lines);
	int i = 0, lur_line = 0, lur_last = set->lines->last;
	
	while(i < E){
		line = set->lines + i;
		if(line->valid == 0){
			//init & miss
			missC++;
			line->tag = tag_id;
			line->valid = 1;
			set->count++;
			line->last = set->count;
			return;
		}else if(line->tag == tag_id){
			//hit
			hitC++;
			set->count++;
			line->last = set->count;
			return;
		}else if(line->last < lur_last){
			//unhit
			lur_last = line->last;
			lur_line = i;
		
		}
		i++;
	}
	
	//evict here
	evictC++;
        missC++;
        line = set->lines + lur_line;
	line->tag = tag_id;
	set->count++;
	line->last = set->count;
