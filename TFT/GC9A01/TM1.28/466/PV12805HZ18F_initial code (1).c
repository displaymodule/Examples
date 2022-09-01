


void main()
{

	Set_POWER(1,0,0,0);//1.8V ON, 2.8V OFF, 5V OFF, BL OFF
	Delay(150);

	Set_POWER(1,1,1,0);//1.8V ON, 2.8V ON, 5V ON, BL OFF
	Delay(500);


	Set_RESET(0,0);//LCD RESET 0
	Delay(100);
	Set_RESET(1,1);//LCD RESET 1
	Delay(200);


	//---------------------------------------------------------------------------------------------------//
	Write_LCD_REG(0x0000,0x00FE);			 
Write_LCD_REG(0x0000,0x00EF); 

Write_LCD_REG(0x0000,0x00EB);	
Write_LCD_REG(0x8000,0x0014); 

Write_LCD_REG(0x0000,0x0084);			
Write_LCD_REG(0x8000,0x0060); //40->60 0x00b5 en  20200924  james

Write_LCD_REG(0x0000,0x0085);
Write_LCD_REG(0x8000,0x00FF); 

Write_LCD_REG(0x0000,0x0086);            
Write_LCD_REG(0x8000,0x00FF); 

Write_LCD_REG(0x0000,0x0087);            
Write_LCD_REG(0x8000,0x00FF);

Write_LCD_REG(0x0000,0x008E);        
Write_LCD_REG(0x8000,0x00FF); 

Write_LCD_REG(0x0000,0x008F);     
Write_LCD_REG(0x8000,0x00FF); 


Write_LCD_REG(0x0000,0x0088);			
Write_LCD_REG(0x8000,0x000A);

Write_LCD_REG(0x0000,0x0089);			
Write_LCD_REG(0x8000,0x0023); ///spi 2data reg en

Write_LCD_REG(0x0000,0x008A);			
Write_LCD_REG(0x8000,0x0000); 

Write_LCD_REG(0x0000,0x008B);			
Write_LCD_REG(0x8000,0x0080); 

Write_LCD_REG(0x0000,0x008C);			
Write_LCD_REG(0x8000,0x0001); 

Write_LCD_REG(0x0000,0x008D);			
Write_LCD_REG(0x8000,0x0003); //99 en

Write_LCD_REG(0x0000,0x00B5);   
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0009);//08->09  james 20200924
Write_LCD_REG(0x8000,0x0014);
Write_LCD_REG(0x8000,0x0008);
//��ɨ
Write_LCD_REG(0x0000,0x00B6);			
Write_LCD_REG(0x8000,0x0000); 
Write_LCD_REG(0x8000,0x0000); //GS  SS  0x0020



Write_LCD_REG(0x0000,0x0036);			
Write_LCD_REG(0x8000,0x0048);

Write_LCD_REG(0x0000,0x003A);			
Write_LCD_REG(0x8000,0x0005); 


Write_LCD_REG(0x0000,0x0090);			
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0008); 

Write_LCD_REG(0x0000,0x00BD);			
Write_LCD_REG(0x8000,0x0006);

Write_LCD_REG(0x0000,0x00BC);			
Write_LCD_REG(0x8000,0x0000);	

Write_LCD_REG(0x0000,0x00FF);			
Write_LCD_REG(0x8000,0x0060);
Write_LCD_REG(0x8000,0x0001);
Write_LCD_REG(0x8000,0x0004);

Write_LCD_REG(0x0000,0x00C3);			
Write_LCD_REG(0x8000,0x001d);//1d
Write_LCD_REG(0x0000,0x00C4);			
Write_LCD_REG(0x8000,0x001d);//1d

Write_LCD_REG(0x0000,0x00C9);			
Write_LCD_REG(0x8000,0x0025);

Write_LCD_REG(0x0000,0x00BE);			
Write_LCD_REG(0x8000,0x0011); 

Write_LCD_REG(0x0000,0x00E1);
Write_LCD_REG(0x8000,0x0010);
Write_LCD_REG(0x8000,0x000E);

Write_LCD_REG(0x0000,0x00DF);			
Write_LCD_REG(0x8000,0x0021);
Write_LCD_REG(0x8000,0x000c);
Write_LCD_REG(0x8000,0x0002);

Write_LCD_REG(0x0000,0x00F0);   
Write_LCD_REG(0x8000,0x0045);
Write_LCD_REG(0x8000,0x0009);
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0026);
Write_LCD_REG(0x8000,0x002A);

Write_LCD_REG(0x0000,0x00F1);    
Write_LCD_REG(0x8000,0x0043);
Write_LCD_REG(0x8000,0x0070);
Write_LCD_REG(0x8000,0x0072);
Write_LCD_REG(0x8000,0x0036);
Write_LCD_REG(0x8000,0x0037);  
Write_LCD_REG(0x8000,0x006F);


Write_LCD_REG(0x0000,0x00F2);   
Write_LCD_REG(0x8000,0x0045);
Write_LCD_REG(0x8000,0x0009);
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0026);
Write_LCD_REG(0x8000,0x002A);

Write_LCD_REG(0x0000,0x00F3);   
Write_LCD_REG(0x8000,0x0043);
Write_LCD_REG(0x8000,0x0070);
Write_LCD_REG(0x8000,0x0072);
Write_LCD_REG(0x8000,0x0036);
Write_LCD_REG(0x8000,0x0037); 
Write_LCD_REG(0x8000,0x006F);

Write_LCD_REG(0x0000,0x00ED);	
Write_LCD_REG(0x8000,0x001B); 
Write_LCD_REG(0x8000,0x000B); 

Write_LCD_REG(0x0000,0x00AE);			
Write_LCD_REG(0x8000,0x0077);

Write_LCD_REG(0x0000,0x00CD);			
Write_LCD_REG(0x8000,0x0063);		


Write_LCD_REG(0x0000,0x0070);			
Write_LCD_REG(0x8000,0x0007);
Write_LCD_REG(0x8000,0x0007);
Write_LCD_REG(0x8000,0x0004);
Write_LCD_REG(0x8000,0x000E); 
Write_LCD_REG(0x8000,0x0010);//0f 
Write_LCD_REG(0x8000,0x0009);
Write_LCD_REG(0x8000,0x0007);
Write_LCD_REG(0x8000,0x0008);
Write_LCD_REG(0x8000,0x0003);

Write_LCD_REG(0x0000,0x00E8);			
Write_LCD_REG(0x8000,0x0044);//34x  14x
/////////////////////////////////////////////
Write_LCD_REG(0x0000,0x0060);		
Write_LCD_REG(0x8000,0x0038);
Write_LCD_REG(0x8000,0x000B);
Write_LCD_REG(0x8000,0x006D);
Write_LCD_REG(0x8000,0x006D);

Write_LCD_REG(0x8000,0x0039);
Write_LCD_REG(0x8000,0x00F0);
Write_LCD_REG(0x8000,0x006D);
Write_LCD_REG(0x8000,0x006D);


Write_LCD_REG(0x0000,0x0061);
Write_LCD_REG(0x8000,0x0038);
Write_LCD_REG(0x8000,0x00F4);
Write_LCD_REG(0x8000,0x006D);
Write_LCD_REG(0x8000,0x006D);

Write_LCD_REG(0x8000,0x0038);
//Write_LCD_REG(0x8000,0x00F7); //20200718
Write_LCD_REG(0x8000,0x00F7);
Write_LCD_REG(0x8000,0x006D);
Write_LCD_REG(0x8000,0x006D);
/////////////////////////////////////
Write_LCD_REG(0x0000,0x0062);
Write_LCD_REG(0x8000,0x0038);
Write_LCD_REG(0x8000,0x000D);
Write_LCD_REG(0x8000,0x0071);
Write_LCD_REG(0x8000,0x00ED);
Write_LCD_REG(0x8000,0x0070);
Write_LCD_REG(0x8000,0x0070);
Write_LCD_REG(0x8000,0x0038);
Write_LCD_REG(0x8000,0x000F);
Write_LCD_REG(0x8000,0x0071);
Write_LCD_REG(0x8000,0x00EF);
Write_LCD_REG(0x8000,0x0070); 
Write_LCD_REG(0x8000,0x0070);

Write_LCD_REG(0x0000,0x0063);			
Write_LCD_REG(0x8000,0x0038);
Write_LCD_REG(0x8000,0x0011);
Write_LCD_REG(0x8000,0x0071);
Write_LCD_REG(0x8000,0x00F1);
Write_LCD_REG(0x8000,0x0070);
Write_LCD_REG(0x8000,0x0070);
Write_LCD_REG(0x8000,0x0038);
Write_LCD_REG(0x8000,0x0013);
Write_LCD_REG(0x8000,0x0071);
Write_LCD_REG(0x8000,0x00F3);
Write_LCD_REG(0x8000,0x0070); 
Write_LCD_REG(0x8000,0x0070);
///////////////////////////////////////////////////////
Write_LCD_REG(0x0000,0x0064);			
Write_LCD_REG(0x8000,0x0028);
Write_LCD_REG(0x8000,0x0029);
Write_LCD_REG(0x8000,0x00F1);
Write_LCD_REG(0x8000,0x0001);
Write_LCD_REG(0x8000,0x00F1);
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x0007);

//��ɨ
Write_LCD_REG(0x0000,0x0066);			
Write_LCD_REG(0x8000,0x003C);
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x00CD);
Write_LCD_REG(0x8000,0x0067);
Write_LCD_REG(0x8000,0x0045);
Write_LCD_REG(0x8000,0x0045);
Write_LCD_REG(0x8000,0x0010);
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x0000);

Write_LCD_REG(0x0000,0x0067);			
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x003C);
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x0000);
Write_LCD_REG(0x8000,0x0001);
Write_LCD_REG(0x8000,0x0054);
Write_LCD_REG(0x8000,0x0010);
Write_LCD_REG(0x8000,0x0032);
Write_LCD_REG(0x8000,0x0098);


					
Write_LCD_REG(0x0000,0x0074);			
Write_LCD_REG(0x8000,0x0010);	
Write_LCD_REG(0x8000,0x0085);	
Write_LCD_REG(0x8000,0x0080);
Write_LCD_REG(0x8000,0x0000); 
Write_LCD_REG(0x8000,0x0000); 
Write_LCD_REG(0x8000,0x004E);
Write_LCD_REG(0x8000,0x0000);					

Write_LCD_REG(0x0000,0x0098);			
Write_LCD_REG(0x8000,0x003e);
Write_LCD_REG(0x8000,0x0007);
Write_LCD_REG(0x0000,0x0099);	//bvee 2x		
Write_LCD_REG(0x8000,0x003e);
Write_LCD_REG(0x8000,0x0007);

//Write_LCD_REG(0x0000,0x00c1);	
//Write_LCD_REG(0x8000,0x0002); 



Write_LCD_REG(0x0000,0x0035);	
Write_LCD_REG(0x8000,0x0000); 
Write_LCD_REG(0x0000,0x0021);
Delay(120);
//--------end gamma setting--------------//

Write_LCD_REG(0x0000,0x0011);
Delay(120);
Write_LCD_REG(0x0000,0x0029);

Write_LCD_REG(0x0000,0x002C);



Write_LCD_REG(0x0000, 0x0029);     
Write_LCD_REG(0x0000, 0x002A);     //Column Address Set
Write_LCD_REG(0x8000,0x0000);   
Write_LCD_REG(0x8000,0x0000);   //0
Write_LCD_REG(0x8000,0x0000);   
Write_LCD_REG(0x8000,0x00eF);   //239

Write_LCD_REG(0x0000, 0x002B);     //Row Address Set
Write_LCD_REG(0x8000,0x0000);   
Write_LCD_REG(0x8000,0x0000);   //0
Write_LCD_REG(0x8000,0x0000);   
Write_LCD_REG(0x8000,0x00eF);   //239

Write_LCD_REG(0x0000, 0x002c);
	


}