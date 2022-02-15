
/* Function to clear the Buffer */
void n5110_clear_buffer(unsigned char screen_buffer[][84]){
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<64;j++){
			screen_buffer[i][j] = 0;
		}
	}
}


void n5110_print_buffer(unsigned char screen_buffer[][84]){
   	int i,j;
	n5110_clear();
	n5110_pos(0,0);
	

	W_GP(PA,1,HIGH);
	for(i=0;i<6;i++){
		for(j=0;j<84;j++){
			spi_tx(1,screen_buffer[i][j]);
		}
	}
	W_GP(PA,1,LOW);

}


/* Function to update the Buffer*/
void n5110_update_buffer(ImgType img, unsigned short img_number, unsigned char screen_buffer[][84]){
	int x_dir, y_dir, x_end, y_end, counter;
	
	if( (img.w + img.x) > 84){
		x_end = 83;
	}else{
		x_end = img.w + img.x - 1;
	}
	
	if( (img.h + img.y) > 5){
		y_end = 5;
	}else{
		y_end = img.h + img.y - 1;
	}
	
	counter = 0;
	
	for(y_dir = img.y; y_dir <= y_end ; y_dir++){
		for(x_dir = img.x; x_dir <= x_end; x_dir++){
			/*Es una forma optimizada de acceder a las imagenes. */
			counter = (y_dir - img.y) * img.w + x_dir - img.x;
			screen_buffer[y_dir][x_dir] = img.image[img_number][counter];
		}
	}


}

void n5110_update_str_buffer(short y, short x,char str[], unsigned char screen_buffer[][84]){
	int i,j, cnt_col,cnt_row;
		
	cnt_col = x;
	cnt_row = y;
	i=0;
	
	while(str[i]){
		if(cnt_row > 5){ break;} //!!!!!!!!!
		for(j=0; j<5; j++){
			screen_buffer[cnt_row][cnt_col] = ASCII[str[i]-32][j];
			if ( (cnt_col + 1 ) > 83){
				if ( (cnt_row + 1) > 5 ){ break;}
				else{
					cnt_row++;
					cnt_col = x;	//Restart
				}
				
			}else{
				cnt_col++;
			}
			
		}
		i++;
	
	
	}


}

