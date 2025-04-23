/*
	setup n59s on GPU kernel

*/


__constant ulong MOD = (ulong)258559632607830;


__kernel void setupn(__global ulong *n43_d, __global ulong *n59_0, __global ulong *n59_1, ulong S53, ulong S47, ulong S43){

	int i = get_global_id(0);
	ulong n43, n47, n53;
	int i43, i47, i53;
	int count;

	if(i<10840){

		n43 = n43_d[i];

		if(i<5420){
			count = i * 12673;
		}
		else{
			count = (i-5420) * 12673;
		}

		for(i43=17;i43>2;i43--){
			n47=n43;
			for(i47=21;i47>2;i47--){
				n53=n47;
				for(i53=27;i53>2;i53--){
					//n59=n53;
					if(i<5420){
						n59_0[count] = n53;
					}
					else{
						n59_1[count] = n53;
					}
					count++;

					n53+=S53;
					if(n53>=MOD)n53-=MOD;
				}
				n47+=S47;
				if(n47>=MOD)n47-=MOD;
			}
			n43+=S43;
			if(n43>=MOD)n43-=MOD;
		}

	}

}


