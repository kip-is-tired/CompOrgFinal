// EncryptData.cpp
//
// This file uses the input data and key information to encrypt the input data
//

#include "Main.h"

// YOU WILL DELETE ALL THIS CODE WHEN YOU DO YOUR PROJECT - THIS IS GIVING YOU EXAMPLES OF HOW TO 
// ACCESS gPasswordHash AND gKey

void encryptData_01(char *data, int datalength)
{

	///*
	int index;
	__asm
	{
		

		//setting round to zero
		xor ebx, ebx
		mov gNumRounds, ebx //ebx free to use again

		//loading in password hash to esi
		lea	esi, gPasswordHash
		xor eax, eax
		
		mov ah, byte ptr [esi] 
		mov al, byte ptr [esi + 1]
		
		
		mov [index], eax //eax free to use again


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
		mov bl, byte ptr [esi + ecx]; //datax
		xor bl, dl;
		xor eax, eax;
		mov al, bl
		mov [esi + ecx], al;
		
		inc ecx				;
		cmp ecx, datalength	;
		jl loop1;

		

	
	}



	return; 
} // encryptData_01

void encryptData_02(char* data, int datalength)
{

	///*
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

		
		mov esi, [data] //data is in esi


		//for loop

	loop1:
			nop
			nop
			nop
			nop
			nop
			//mov bl, byte ptr [edi + edx];
			mov bl, byte ptr[esi + ecx]; //datax
			xor bl, dl;

			xor eax, eax;
			mov al, bl;
			mov bh, bl;
			xor ebx, ebx; //freeing bl to use in reverse fx
				//mov[esi + ecx], al; //al holds data x
				//////////////////////////////////////////////////milestone 2 stuff///////////////////////////////////////////////

				////////////////////////////////////////////////////"A" code table swap///////////////////////////////////////////
				//data[x] = codetable[bit at datax]

			mov al, byte ptr[gEncodeTable + eax];
		


			////////////////////////////////////////////////////"D" invert bits 0,2,4,7////////////////////////////////////////
		
			xor al,0x95


			///////////////////////////////////////////////////"C" reverse bit order///////////////////////////////////////////
			push ecx;
			xor ecx, ecx; //pushing ecx to stack and clearing it to use in following loop

		REVERSE:

			
			rcl al, 1;
			rcr bl, 1;

			inc ecx;
			cmp ecx, 8;
			jb REVERSE;

			pop ecx;
			mov al, bl;
///*
			///////////////////////////////////////////////////////"B" nibble rotate out//////////////////////////////////////////

			//top nibble
			mov ah, al; // storing al value in temp 
			xor ebx, ebx; //zeroing ebx for or-ing 
			and ah, 0xf0; //keeping top half of nibble
			shl ah, 1; //rotating a out into carry
			rcl bh, 5; //putting a into the zero'd out bh at the correct index        
			or ah, bh; // or-ing to put a in the correct spot

			//bottom nibble
			xor ebx, ebx; ,//clearing out ebx to work with again
			mov bl, al; //copying al to bl to work with value saftly
			and bl, 0x0f; //keeping bottom half of nibble
			shr bl, 1; // putting h into carry flag
			rcl bh, 4; //going to 0'd register and placing h at the desired position
			or bl, bh; //or-ing to move h in the correct spot of the bottom nibble

			//concating
			add bl, ah; //adding the top and bottom halfs
			mov al, bl; //putting the final value in al
			xor ah, ah;
			
//*/
			/////////////////////////////////////////////////////"E" rotate 2 bits right///////////////////////////////////////
			ror al, 2;
			


	

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//saves new datax in file
			mov[esi + ecx], al;
			inc ecx;
			cmp ecx, datalength;
			jl loop1;




	}



	return;
} // encryptData_02

void encryptData_03(char* data, int datalength)
{

	///*
	int index;
	int hophop;
	int loopcounter;
	__asm
	{


		//setting gNumTracker (my way of referring to this ecx value) to zero, debugging was being wonky
		xor ecx, ecx
		mov [loopcounter], ecx 
		

		NUMROUNDS_LOOP:
		nop //set breakpoint
		nop
		nop
		nop
		nop

		mov ecx, [loopcounter]	

		//loading in password hash to esi
		lea	esi, gPasswordHash
		xor eax, eax

		mov ah, byte ptr[esi + ecx*4]		
		mov al, byte ptr[esi + ecx*4 + 1]		//ax should now have the index val


		////////////////////////////////////////////////hop count setting and if//////////////////////////////////////////////////
		nop //set breakpoint
		nop
		nop
		nop
		nop
		
		xor ebx,ebx								//clearing ebx for hop count
		mov bh, byte ptr[esi + ecx*4 + 2]		//gPasswordHash[2+round*4]
		mov bl, byte ptr[esi + ecx*4 + 3]		//gPasswordHash[3+round*4]


		cmp ebx, 0							//if (hop) not 0
		jne HOP_NOT_ZERO					//skip assigning 0000ffff to hop

		mov ebx, 0x0000ffff					//else sets ebx to 0000ffff

		HOP_NOT_ZERO:

		mov [hophop], ebx					//save value to hophop
		mov[index], eax 


		
		xor ecx, ecx						//counter for loop1


///*	
			loop1:

			// edi acting as gkey, edx acting as index, 
			lea edi, gkey			
			mov edx, [index]		
			

			mov dl, byte ptr[edi + edx]		//gkey  


			mov esi, [data]					//data is in esi
			
			mov bl, byte ptr[esi + ecx]		//data[x]
			xor bl, dl						

			xor eax, eax
			mov al, bl

			nop //set breakpoint
			nop
			nop
			nop
			nop
			nop

				
			xor ebx,ebx
			mov ebx, hophop
			add index, ebx					//index + hop
			cmp [index], 0x10001
			jb INDEX_NOCHANGE				

			sub [index], 0x10001			//subtracts 65537 from index
			

			INDEX_NOCHANGE:

			xor ebx, ebx
			mov bl, al						//data x in bl
			
			
			//////////////////////////////////////////////////milestone 2 stuff///////////////////////////////////////////////

			////////////////////////////////////////////////////"A" code table swap///////////////////////////////////////////
			//data[x] = codetable[bit at datax]

			mov al, byte ptr[gEncodeTable + ebx]



			////////////////////////////////////////////////////"D" invert bits 0,2,4,7////////////////////////////////////////

			xor al, 0x95


			///////////////////////////////////////////////////"C" reverse bit order///////////////////////////////////////////
			push ecx
			xor ecx, ecx					//pushing ecx to stack and clearing it to use in following loop
			xor ebx, ebx					//freeing bl to use in reverse fx

		REVERSE:


			rcl al, 1
			rcr bl, 1

			inc ecx
			cmp ecx, 8
			jb REVERSE

			pop ecx
			mov al, bl
			///*
			///////////////////////////////////////////////////////"B" nibble rotate out//////////////////////////////////////////

			//top nibble
			mov ah, al		// storing al value in temp 
			xor ebx, ebx	//zeroing ebx for or-ing 
			and ah, 0xf0	//keeping top half of nibble
			shl ah, 1		//rotating a out into carry
			rcl bh, 5		//putting a into the zero'd out bh at the correct index        
			or ah, bh		// or-ing to put a in the correct spot

			//bottom nibble
			xor ebx, ebx	//clearing out ebx to work with again
			mov bl, al		//copying al to bl to work with value saftly
			and bl, 0x0f	//keeping bottom half of nibble
			shr bl, 1		//putting h into carry flag
			rcl bh, 4		//going to 0'd register and placing h at the desired position
			or bl, bh		//or-ing to move h in the correct spot of the bottom nibble

			//concating
			add bl, ah		//adding the top and bottom halfs
			mov al, bl		//putting the final value in al
			xor ah, ah

			//*/
						/////////////////////////////////////////////////////"E" rotate 2 bits right///////////////////////////////////////
			ror al, 2




//*/
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//saves new datax in file

			nop //breakpoint
			nop
			nop
			nop
			nop
			nop
			
			mov[esi + ecx], al
			inc ecx
			cmp ecx, datalength
			jl loop1

			nop
			nop
			nop
			nop
			nop


			inc loopcounter
			mov ecx, loopcounter
			cmp gNumRounds, ecx    //gNumRounds - loopcounter

			ja NUMROUNDS_LOOP  //if >= to zero, loop again



	}



	return;
} // encryptData_03



