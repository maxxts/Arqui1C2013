
#include "../include/keyboard.h"
#include "../include/kernel.h"





//TABLA DE SCANCODES
unsigned char key_map[][2]= {

/*0x00*/  {NO_PRINT,NO_PRINT},
/*0x01*/  {NO_PRINT,NO_PRINT}, //Esc
/*0x02*/  {'1','!'}, 
/*0x03*/  {'2','@'}, 
/*0x04*/  {'3','#'}, 
/*0x05*/  {'4','$'}, 
/*0x06*/  {'5','%'}, 
/*0x07*/  {'6','^'}, 
/*0x08*/  {'7','&'}, 
/*0x09*/  {'8','*'}, 
/*0x0A*/  {'9','('}, 
/*0x0B*/  {'0',')'}, 
/*0x0C*/  {'-','_'}, 
/*0x0D*/  {'=','+'}, 
/*0x0E*/  {'\b','\b'},
/*0x0F*/  {'\t','\t'}, //Tab
/*0x10*/  {'q','Q'}, 
/*0x11*/  {'w','W'}, 
/*0x12*/  {'e','E'}, 
/*0x13*/  {'r','R'}, 
/*0x14*/  {'t','T'}, 
/*0x15*/  {'y','Y'}, 
/*0x16*/  {'u','U'}, 
/*0x17*/  {'i','I'}, 
/*0x18*/  {'o','O'}, 
/*0x19*/  {'p','P'}, 
/*0x1A*/  {'[','{'}, 
/*0x1B*/  {']','}'}, 
/*0x1C*/  {'\n','\n'},
/*0x1D*/  {NO_PRINT,NO_PRINT}, //Left Ctrl
/*0x1E*/  {'a','A'}, 
/*0x1F*/  {'s','S'}, 
/*0x20*/  {'d','D'}, 
/*0x21*/  {'f','F'}, 
/*0x22*/  {'g','G'}, 
/*0x23*/  {'h','H'}, 
/*0x24*/  {'j','J'}, 
/*0x25*/  {'k','K'}, 
/*0x26*/  {'l','L'}, 
/*0x27*/  {';',':'},  
/*0x28*/  {'\'','"'}, 
/*0x29*/  {'`','~'}, 
/*0x2A*/  {NO_PRINT,NO_PRINT}, //Left Shift
/*0x2B*/  {'\\','|'}, 
/*0x2C*/  {'z','Z'}, 
/*0x2D*/  {'x','X'}, 
/*0x2E*/  {'c','C'}, 
/*0x2F*/  {'v','V'}, 
/*0x30*/  {'b','B'}, 
/*0x31*/  {'n','N'}, 
/*0x32*/  {'m','M'}, 
/*0x33*/  {',','<'}, 
/*0x34*/  {'.','>'}, 
/*0x35*/  {'/','?'}, 
/*0x36*/  {NO_PRINT,NO_PRINT}, //Right Shift
/*0x37*/  {NO_PRINT,NO_PRINT},
/*0x38*/  {NO_PRINT,NO_PRINT}, //Left Alt
/*0x39*/  {' ',' '}, 
/*0x3A*/  {NO_PRINT,NO_PRINT}, //Caps Lock
/*0x3B*/  {NO_PRINT,NO_PRINT}, //F1
/*0x3C*/  {NO_PRINT,NO_PRINT}, //F2
/*0x3D*/  {NO_PRINT,NO_PRINT}, //F3
/*0x3E*/  {NO_PRINT,NO_PRINT}, //F4
/*0x3F*/  {NO_PRINT,NO_PRINT}, //F5
/*0x40*/  {NO_PRINT,NO_PRINT}, //F6
/*0x41*/  {NO_PRINT,NO_PRINT}, //F7
/*0x42*/  {NO_PRINT,NO_PRINT}, //F8
/*0x43*/  {NO_PRINT,NO_PRINT}, //F9
/*0x44*/  {NO_PRINT,NO_PRINT}, //F10
/*0x45*/  {NO_PRINT,NO_PRINT}, //Num Lock
/*0x46*/  {NO_PRINT,NO_PRINT}, //Scroll Lock
/*0x47*/  {NO_PRINT,NO_PRINT}, //Keypad 7
/*0x48*/  {NO_PRINT,NO_PRINT}, //Keypad 8 OR Up-Arrow
/*0x49*/  {NO_PRINT,NO_PRINT}, //Keypad 9
/*0x4A*/  {NO_PRINT,NO_PRINT}, //Keypad -
/*0x4B*/  {NO_PRINT,NO_PRINT}, //Keypad 4
/*0x4C*/  {NO_PRINT,NO_PRINT}, //Keypad 5
/*0x4D*/  {NO_PRINT,NO_PRINT}, //Keypad 6
/*0x4E*/  {NO_PRINT,NO_PRINT}, //Keypad +
/*0x4F*/  {NO_PRINT,NO_PRINT}, //Keypad 1
/*0x50*/  {NO_PRINT,NO_PRINT}, //Keypad 2 OR Down-Arrow
/*0x51*/  {NO_PRINT,NO_PRINT}, //Keypad 3
/*0x52*/  {NO_PRINT,NO_PRINT}, //Keypad 0
/*0x53*/  {NO_PRINT,NO_PRINT}, //Keypad . // Supr
/*0x54*/  {NO_PRINT,NO_PRINT}, //Sys Req (AT)
/*0x55*/  {'+','*'}, 
/*0x56*/  {'+','*'}, 
/*0x57*/  {NO_PRINT,NO_PRINT}, //F11
/*0x58*/  {NO_PRINT,NO_PRINT}}; //F12


int status_RSHIFT = 0;
int status_LSHIFT = 0;
int status_SHIFT = 0;
int status_CAPS = 0;



void scanStatus(int scode){
	
	switch (scode){
		case 0x2A:
			status_LSHIFT = 1;
			break;
		case 0x36:
			status_RSHIFT = 1;
			break;
		case 0x2A+0x80: //Sumando 0x80 obtengo el codigo de "release" de una tecla. (http://en.wikipedia.org/wiki/Scancode)
			status_LSHIFT = 0;
			break;

		case 0x36+0x80:
			status_RSHIFT = 0;
			break;

		case 0x3A:
			status_CAPS = !status_CAPS;
			break;	
		default: 	
			break;
	}

}

//Checkea si es un caracter alfabetico. Sera utilizado para definir el comportamiento del "CAPS LOCK"
int isAlpha(int scode){

	if( (scode>=0x10 && scode<=0x19) || (scode>=0x1E && scode<=0x26) || (scode>=0x2C && 													scode<=0x32)){
		return 1;
	}
	return 0;
}




//RUTINA DE ATENCION DE INTERRUPCION PARA TECLADO
void int_09 (int scode){
	

	
	
	char toPrint;

	
	//Me fijo si tengo que cambiar algun estado
	scanStatus(scode);

	//Evaluo ambos Shift
	if (status_LSHIFT || status_RSHIFT){
		status_SHIFT = 1;
	}
	
	
	
	//Valido que el Scan Code sea valido
	if (scode >= 0x01 && scode <= 0x58)
	{
		
		//Valido que sea un caracter que puede ser mostrado en pantalla
		if (key_map[scode][0] != NO_PRINT)
		{

			if (isAlpha(scode)) {

				if ( (status_CAPS && status_SHIFT) || (!status_CAPS && !status_SHIFT)) {
				
					//CAPSySHIFT o NINGUNO -> Sin mayusculas
					toPrint = key_map[scode][0];
					
				} else if (status_CAPS || status_SHIFT)	{

					//SOLO UNO DE LOS DOS -> Mayusculas normales
					toPrint = key_map[scode][1];

				}			
				
			}else{
			
				//Es un numero o simbolo - IGNORO EL CAPS
				if (status_SHIFT) {
				
					toPrint = key_map[scode][1]; //MAYUS
				
				}else{
				
					toPrint = key_map[scode][0]; //MINUS
								
				}			
			
			}		

		}
	
	__write(1,&toPrint,1); //IMPRIMO - TEST
		
	}

	

}









//












