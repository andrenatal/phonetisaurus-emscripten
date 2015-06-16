/*
 Copyright (c) [2012-], Josef Robert Novak
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
  modification, are permitted #provided that the following conditions
  are met:

 * Redistributions of source code must retain the above copyright 
    notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above 
    copyright notice, this list of #conditions and the following 
    disclaimer in the documentation and/or other materials provided 
    with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "Phonetisaurus.hpp"
#include "util.hpp"
using namespace fst;

int phoneticizeWord(
		     const char* g2pmodel_file, string testword, 
		     int nbest, string sep, bool mbrdecoder, float alpha, float precision, float ratio, int order,
		     int beam=500, int output_words=0 ){

  if(testword == ""){
	return -1;
  }

    
  Phonetisaurus phonetisaurus( g2pmodel_file, mbrdecoder, alpha, precision, ratio, order );

  if(phonetisaurus.g2pmodel == NULL)
  {
	  return -1;
  }

  vector<string>   entry = tokenize_entry( &testword, &sep, phonetisaurus.isyms );

  vector<PathData> paths = phonetisaurus.phoneticize( entry, nbest, beam );

  if( output_words==0 ){
    while( phonetisaurus.printPaths( paths, nbest, "", "" )==true ){
      nbest++;
      paths = phonetisaurus.phoneticize( entry, nbest, beam );
    }
  }else{
    while( phonetisaurus.printPaths( paths, nbest, "", testword )==true){
      nbest++;
      paths = phonetisaurus.phoneticize( entry, nbest, beam );
    }
  }

  return 0;
}



DEFINE_string( model,     "asset_dir/model.fst", "The input WFST G2P model.");
DEFINE_string( input,     "", "A word or test file.");
DEFINE_bool(   isfile, false, "'--input' is a file.");
DEFINE_int32(  nbest,      1, "Print out the N-best pronunciations.");
DEFINE_int32(  beam,     500, "N-best search beam.");
DEFINE_string( sep,       "", "Separator token for input words.");
DEFINE_bool(   mbr,    false, "Use the Lattice Minimum Bayes-Risk decoder");
DEFINE_bool(   words,  false, "Output words with hypotheses.");
DEFINE_double( alpha,    0.6, "The alpha LM scale factor for the LMBR decoder.");
DEFINE_int32(  order,      6, "The N-gram order for the MBR decoder.");
DEFINE_double( prec,    0.85, "The N-gram precision factor for the LMBR decoder.");
DEFINE_double( ratio,   0.72, "The N-gram ratio factor for the LMBR decoder.");

int main( int argc, char **argv ) {
  string usage = "phonetisaurus-g2p decoder.\n\n Usage: ";
  set_new_handler(FailedNewHandler);
  SetFlags(usage.c_str(), &argc, &argv, false );

    //Otherwise we just have a word
    phoneticizeWord(    
		    FLAGS_model.c_str(), FLAGS_input, FLAGS_nbest, 
		    FLAGS_sep, FLAGS_mbr, FLAGS_alpha, FLAGS_prec, 
		    FLAGS_ratio, FLAGS_order, FLAGS_beam, FLAGS_words
			);
  return 1;
}
