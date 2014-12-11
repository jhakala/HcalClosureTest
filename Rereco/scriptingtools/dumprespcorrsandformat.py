##########
# This program takes the HcalClosureTest code's generated response corrections and reformats them so they can be used in the rereco routine.
# It needs a template of reference HCAL response corrections, referred to as "template", and the response corrections from HcalClosureTest, referred to as "file".
# It creates the formatted HCAL response corrections that are ready to go into the rereco, referred to as "out_file".
#######

import ROOT as r
import re

file = r.TFile("DijetRespCorrs.root")
# change this file ^^^ to point to the generated dijet balancing respcorrs.

template = open("scriptingtools/Reference_MC_RespCorrs_fromSalavat.txt", "r")
out_file =  open("scriptingtools/output.txt", "w");
hist=file.Get("h_corr")

# go through each line of the template
lines=template.readlines()
num_lines = len(lines)


for i in range (0,num_lines):	
		#keep the title line
		if i==0:
			bits = re.split('\s+', lines[i])
			#make sure the columns come out with nice human readability
			bits[0] = bits[0]+"      "
			for j in range (1, len(bits)):
				bits[j]=bits[j].rjust(7)
			out_file.write( '          '.join(bits)+'\n')	
		else:
			bits = re.split('\s+', lines[i])
			# change response correction column for the HB, HE, and HF. I leave HO out since we use run1 data. I leave out ZDC since it will be read out by CASTOR in run2.
			if bits[4] in ('HB', 'HE', 'HF'):
				bits[5] = "%.6f" % (float(bits[5])*hist.GetBinContent(int(bits[1])+42))		
			# The last line modifies the respcorrs by multipling the dijet balancing respcorrs with the reference respcorrs.			

			for j in range (0, len(bits)):
				bits[j]=bits[j].rjust(7)
			# join it back together and write it out
			out_file.write( '          '.join(bits)+'\n')

template.close()
out_file.close()

