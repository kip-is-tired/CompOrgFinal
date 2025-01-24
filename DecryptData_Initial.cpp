// DecryptData.cpp
//
// THis file uses the input data and key information to decrypt the input data
//

#include "Main.h"


void decryptData_01(char *data, int sized)
{
	
	int index;
	__asm
	{


		//setting round to zero
		xor ebx, ebx
		mov gNumRounds, ebx //ebx free to use again

		//loading in password hash to esi
		lea	esi, gPasswordHash
		xor eax, eax

		mov ah, byte ptr[esi]
		mov al, byte ptr[esi + 1]

		mov[index], eax //eax free to use again


		//counter for for loop
		xor ecx, ecx

		// edi acting as gkey, edx acting as index, 
		lea edi, gkey
		mov edx, index
		
		mov dl, byte ptr[edi + edx] //gkey

		
		mov esi, [data]


		//for loop

	loop1:

			//mov bl, byte ptr [edi + edx];
			mov bl, byte ptr[esi + ecx]; //datax
			xor bl, dl;
			xor bl, dl;
			xor eax, eax;
			mov al, bl
				mov[esi + ecx], al;
			//milestone 2 stuff
			inc ecx;
			cmp ecx, sized;
			jl loop1;




	}



	return;
} // DecryptData_01

void decryptData_02(char* data, int sized)
{

	int index;
	__asm
	{


		//setting round to zero
		xor ebx, ebx
		mov gNumRounds, ebx //ebx free to use again

		//loading in password hash to esi
		lea	esi, gPasswordHash
		xor eax, eax

		mov ah, byte ptr[esi]
		mov al, byte ptr[esi + 1]

		mov[index], eax //eax free to use again


		//counter for for loop
		xor ecx, ecx

		// edi acting as gkey, edx acting as index, 
		lea edi, gkey
		mov edx, index
		
		mov dl, byte ptr[edi + edx] //gkey

		
		mov esi, [data]


		//for loop

	loop1:

			nop
			nop
			nop
			nop
			nop
			nop

			mov bl, byte ptr[esi + ecx]; //datax
			xor eax, eax;
			mov al, bl
			
				// milstone 2/////////////////////////////////////////////////////


			//E rotate 2 bits right
			rol al, 2;

				///*
			//B nibble rotate out

			//top nibble
			mov ah, al; // storing al value in temp 
			xor ebx, ebx; //zeroing ebx for or-ing 
			and ah, 0xf0; //keeping top half of nibble
			shl ah, 1; //rotating b out into carry
			rcl bh, 1; //putting b into the zero'd out bh 
			shl ah, 1; //putting c into the carry
			rcl bh, 1; //putting c into bh
			shl ah, 1; //putting d into the carry
			rcl bh, 1; //putting d into bh
			shl bh, 4; //correcting the positions of b,c,d
			
			or ah, bh; // or-ing to put a in the correct spot
			and ah, 0xf0; //making sure top is still clear

			//bottom nibble
			xor ebx, ebx; ,//clearing out ebx to work with again
			mov bl, al; //copying al to bl to work with value saftly
			and bl, 0x0f; //keeping bottom half of nibble
			shr bl, 1; // putting g into carry flag
			rcr bh, 1; //going to 0'd register and placing g
			shr bl, 1; //putting f into the carry flag
			rcr bh, 1; // putting f into bh
			shr bl, 1; // putting e into carry
			rcr bh, 1; // putting e into bh
			shr bh, 4; //correcting the positions of e,f,g
			or bl, bh; //or-ing to move h in the correct spot of the bottom nibble
			and bl, 0x0f; //making sure bottom is still clear

			//concating
			add bl, ah; //adding the top and bottom halfs
			mov al, bl; //putting the final value in al
			xor ah, ah;
//*/


						//C reverse bit order
			push ecx;
			xor ecx, ecx;

			push edx;
			xor edx, edx // clearing out edx to use for reverse order. encrypt uses ebx for this but wires get crossed in decrypt

		REVERSE:

			rcl al, 1;
			rcr dl, 1;

			inc ecx;
			cmp ecx, 8;
			jb REVERSE;

			
			mov al, dl;
			pop edx;
			pop ecx;
				
				//D invert bits 0,2,4,7

			xor al, 0x95

				//'A' code table swap
				//codetable[bit at datax] = data[x] 

			mov al, byte ptr[gDecodeTable + eax]

			xor al, dl;
			mov[esi + ecx], al; //moving into data
			
			inc ecx;
			cmp ecx, sized;
			jl loop1;




	}



	return;
} // DecryptData_02


void decryptData_03(char* data, int sized)
{

	int index;
	int hophop;
	
	__asm
	{


		

		NUMROUNDS_LOOP:
		nop
		nop
		nop
		nop
		nop

		xor ecx, ecx
		mov ecx, gNumRounds
		dec ecx								//dec because gNumRounds is 1 extra for calculations

		//loading in password hash to esi
		lea	esi, gPasswordHash
		xor eax, eax

		mov ah, byte ptr[esi+ ecx*4]
		mov al, byte ptr[esi + ecx*4 + 1]

		mov[index], eax 

		////////////////////////////////////////////////hop count setting and if//////////////////////////////////////////////////
		nop //set breakpoint
		nop
		nop
		nop
		nop

		xor ebx, ebx							//clearing ebx for hop count
		mov bh, byte ptr[esi + ecx * 4 + 2]		//gPasswordHash[2+round*4]
		mov bl, byte ptr[esi + ecx * 4 + 3]		//gPasswordHash[3+round*4]


		cmp ebx, 0						//if hop not 0
		jne HOP_NOT_ZERO				//skip assigning 0000ffff to hop

		mov [ebx], 0x0000ffff			//else sets hop to 0000ffff

		HOP_NOT_ZERO:

		mov [hophop], ebx
		
		xor ecx, ecx					//counter for for loop

		

	loop1:

			nop
			nop
			nop
			nop
			nop
			nop

			// edi acting as gkey, edx acting as index, 
			lea edi, gkey
			xor edx,edx
			mov edx, [index]		
		

			mov dl, byte ptr[edi + edx]	//gkey


			mov esi, [data]

			mov bl, byte ptr[esi + ecx]	//datax
			xor eax, eax
			mov al, bl

	
			/////////////////////////////////////////////// E rotate 2 bits right//////////////////////////////////////////////////////
			rol al, 2

			///*
			/////////////////////////////////////////////// B nibble rotate out ///////////////////////////////////////////////////////

			//top nibble
			mov ah, al					// storing al value in temp 
			xor ebx, ebx				//zeroing ebx for or-ing 
			and ah, 0xf0				//keeping top half of nibble
			shl ah, 1					//rotating b out into carry
			rcl bh, 1					//putting b into the zero'd out bh 
			shl ah, 1					//putting c into the carry
			rcl bh, 1					//putting c into bh
			shl ah, 1					//putting d into the carry
			rcl bh, 1					//putting d into bh
			shl bh, 4					//correcting the positions of b,c,d

			or ah, bh					// or-ing to put a in the correct spot
			and ah, 0xf0				//making sure top is still clear

			//bottom nibble
			xor ebx, ebx				//clearing out ebx to work with again
			mov bl, al					//copying al to bl to work with value saftly
			and bl, 0x0f				//keeping bottom half of nibble
			shr bl, 1					// putting g into carry flag
			rcr bh, 1					//going to 0'd register and placing g
			shr bl, 1					//putting f into the carry flag
			rcr bh, 1					// putting f into bh
			shr bl, 1					// putting e into carry
			rcr bh, 1					// putting e into bh
			shr bh, 4					//correcting the positions of e,f,g
			or bl, bh					//or-ing to move h in the correct spot of the bottom nibble
			and bl, 0x0f				//making sure bottom is still clear

			//concating
			add bl, ah					//adding the top and bottom halfs
			mov al, bl					//putting the final value in al
			xor ah, ah
			//*/


			////////////////////////////////////////////////// C reverse bit order///////////////////////////////////////////////////////////
			push ecx
			xor ecx, ecx

			push edx
			xor edx, edx				// clearing out edx to use for reverse order. encrypt uses ebx for this but wires get crossed in decrypt

			REVERSE :

			rcl al, 1
			rcr dl, 1

			inc ecx
			cmp ecx, 8
			jb REVERSE


			mov al, dl
			pop edx
			pop ecx

			/////////////////////////////////////////////////// D invert bits 0,2,4,7 ///////////////////////////////////////////////////////////

			xor al, 0x95

			//'A' code table swap
			//codetable[bit at datax] = data[x] 

			mov al, byte ptr[gDecodeTable + eax]

			

			/////////////////////////////////////////////////////// index+= hophop and if statement///////////////////////////////////////////
//*/		

			mov edx, [index]
			mov edx, [edi+edx]			//gkey at index

			// prev code
			xor al, dl					//assuming dl is gkey at index
			
			mov[esi + ecx], al;			//moving into data

			xor ebx, ebx
			mov ebx, hophop
			add index, ebx				//index+hop

			cmp [index], 0x10001		//subtracts 65537 from index
			jb INDEX_NOCHANGE

			sub [index], 0x10001		//subtracts 65537 from index

			INDEX_NOCHANGE:

			inc ecx
			cmp ecx, sized
			jl loop1

			
			dec gNumRounds
			ja NUMROUNDS_LOOP
			


	}



	return;
} // DecryptData_03
