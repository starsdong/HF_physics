#include <stdio.h>
#include "iomanip.h"

void scale()
{
  gROOT->Reset();

  const Int_t N = 1;
  const Int_t NMAX = 100;
  const Int_t NP[N] = {4};
  const Double_t Tc = 0.154;
  const Double_t twoPi = 3.14159*2.;
  Double_t x[N][NMAX], y[N][NMAX], yel[N][NMAX], yeu[N][NMAX];
  // Char_t *FileName[N] = {"../data/LQCD/fit_ds.dat"};
  // Char_t *OutFileName[N] = {"../data/LQCD/fit_ds_scale.dat"};
  // Char_t *OutRootName[N] = {"../data/LQCD/fit_ds_scale.root"};
  Char_t *FileName[N] = {"../data/LQCD/ds.dat"};
  Char_t *OutFileName[N] = {"../data/LQCD/ds_scale.dat"};
  Char_t *OutRootName[N] = {"../data/LQCD/ds_scale.root"};
  Char_t *Name[N] = {"LQCD"};

  TGraphAsymmErrors *gr[N];
  ifstream inData;
  
  for(int i=0;i<N;i++) {
    inData.open(FileName[i]);
    for(int j=0;j<NP[i];j++) {
      double a,b,c,d;
      inData >> a >> b >> c >> d;
      x[i][j] = a*Tc;
      y[i][j] = b*twoPi;
      yel[i][j] = (b-d)*twoPi;
      yeu[i][j] = (c-b)*twoPi;      
    }
    inData.close();
    

    ofstream outData;
    outData.open(OutFileName[i]);
    for(int j=0;j<NP[i];j++) {
      outData << setw(10) << x[i][j] << setw(10) << y[i][j] << setw(10) << yel[i][j] << setw(10) << yeu[i][j] << endl;
    }
    outData.close();
    
    TFile *fout = new TFile(OutRootName[i],"RECREATE");
    gr[i] = new TGraphAsymmErrors(NP[i], x[i], y[i], 0, 0, yel[i], yeu[i]);
    gr[i]->SetName(Form("2piTDs_%s",Name[i]));
    gr[i]->Write();
    fout->Close();
  }


}
