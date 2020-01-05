unit haval;

{$link ../../3rdparty/haval.o}

interface
	uses ctypes;

	type
		haval_word = cuint;

		Phaval_state = ^haval_state;
		haval_state = record
			count: array[0..1] of haval_word;
			fingerprint: array[0..7] of haval_word;
			block: array[0..31] of haval_word;
			remainder: array[0..127] of cuchar;
		end;

	procedure haval_string(s: pcchar; fingerprint: pcuchar); cdecl; external;
	function haval_file(file_name: pcchar; fingerprint: pcuchar): cint; cdecl; external;
	procedure haval_stdin; cdecl; external;
	procedure haval_start(state: Phaval_state); cdecl; external;
	procedure haval_hash(state: Phaval_state; s: pcuchar; str_len: cuint); cdecl; external;
	procedure haval_end(state: Phaval_state; final_fpt: pcuchar); cdecl; external;
	procedure haval_hash_block(state: Phaval_state); cdecl; external;

implementation

end.
