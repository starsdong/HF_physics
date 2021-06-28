#include "stdio.h"
#include <iomanip.h>

void makeQ1c_A(const float T_in = 0.3)
{
  gROOT->Reset();
  const Float_t hbarc = 0.1973;

  const Int_t N = 6;
  const Float_t T_min = 0.16;
  const Float_t T_max = 0.60;
  const Float_t p_min = 0;
  const Float_t p_max = 40.0;
  const Int_t NTMax = 23; // T: 0.16-0.60, 0.02 per bin
  const Int_t NPMax = 201;  // p:  0-40, 0.2 per bin

  Int_t NT[N] = {23,22,22,23,23,23};
  Int_t NP[N] = {201,80,200,151,201,201};
  Char_t *FileName[N] = {"../data/PHSD/charm/homework1c-charm-phsd.dat",
			 "../data/CUJET/LGR/LGR_Q1/Q1_c_EtaD.dat",
			 "../data/Duke/drag.dat",
			 "../data/TAMU/Z_results-data/1c_A_B.txt",
  			 "../data/Catania/Table_Transport_Coefficients.dat",
			 "../data/LBT/LBT/data-1c-LBT-c-friction.dat"};
  const Char_t *Name[N] = {"PHSD","CUJET","Duke","TAMU","Catania","LBT"};
  const Int_t Color[N] = {kBlack, kRed, kGreen+2, kBlue, kOrange+1, kGray+2};
  const Int_t Style[N] = {1, 2, 3, 9, 5, 6};

  const Int_t N_add = 2;
  TGraph *gr_add[N_add];
  const Char_t *Name_add[N_add] = {"Nantes", "Nantes el."};
  const Int_t Color_add[N_add] = {kMagenta+1, kMagenta+1};
  const Int_t Style_add[N_add] = {7, 8};
  
  TGraph *gr[N][NTMax];  // vs. p
  Float_t T[N][NTMax];
  Float_t p[N][NPMax];
  Float_t A[N][NTMax][NPMax];
  Float_t B[N][NTMax][NPMax];
  ifstream inData;
  for(int i=0;i<N;i++) {
    //
    inData.open(FileName[i]);
    switch (i) {
    case 0:   // PHSD
      for(int j=0;j<NT[i];j++) {
	for(int k=0;k<NP[i];k++) {
	  inData >> T[i][j] >> p[i][k] >> A[i][j][k] >> B[i][j][k];
	  //	  A[i][j][k] /= p[i][k];
	}	
      }
      break;
    case 1:   // CUJET
      for(int k=0;k<NP[i];k++) {
	for(int j=0;j<NT[i];j++) {
	  inData >> p[i][k] >> T[i][j] >> A[i][j][k];
	  A[i][j][k] /= hbarc;
	}	
      }
      break;
    case 2:     // Duke
      for(int k=0;k<NP[i];k++) {
	for(int j=0;j<NT[i];j++) {
	  inData >> p[i][k] >> T[i][j] >> A[i][j][k];
	  A[i][j][k] /= hbarc;
	}	
      }
      break;
    case 3:   // TAMU
      for(int j=0;j<NT[i];j++) {
	for(int k=0;k<NP[i];k++) {
	  inData >> T[i][j] >> p[i][k] >> A[i][j][k] >> B[i][j][k];
	}	
      }
      break;
    case 4:    // Catania
      for(int j=0;j<NT[i];j++) {
	for(int k=0;k<NP[i];k++) {
	  inData >> T[i][j] >> p[i][k] >> A[i][j][k] >> B[i][j][k];
	}	
      }
      break;
    case 5:    // LBT
      for(int j=0;j<NT[i];j++) {
	for(int k=0;k<NP[i];k++) {
	  inData >> T[i][j] >> p[i][k] >> A[i][j][k];
	}	
      }
      break;
    default:
      break;
    }
    inData.close();
  }

  for(int i=0;i<N;i++) {
    for(int j=0;j<NT[i];j++) {
      gr[i][j] = new TGraph(NP[i], p[i], A[i][j]);
      gr[i][j]->SetName(Form("%s_%4.2f",Name[i],float(T[i][j]+0.0001)));
      gr[i][j]->SetLineWidth(2);
      gr[i][j]->SetLineColor(i+1);
      gr[i][j]->SetLineStyle(i+1);
    }
  }

  int iT =  (Int_t) (((T_in+0.0001) - 0.16) / 0.02);
  cout << " T_in = " << T_in << "\t index = " << iT << endl;
  for(int i=0;i<N;i++) {
    cout << FileName[i] << endl;
    gr[i][iT]->Print();
  }

  // Additional
  // Nantes
  if(iT==2) {  // Nantes T = 0.2 GeV
    gr_add[0] = new TGraph("../data/Nantes/task1/A_el_ra_0.2.txt","%lg %lg");
    gr_add[1] = new TGraph("../data/Nantes/task1/A_el_0.2.txt","%lg %lg");
  }
  if(iT==7) {  // Nantes T = 0.3 GeV
    gr_add[0] = new TGraph("../data/Nantes/task1/A_el_ra_0.3.txt","%lg %lg");
    gr_add[1] = new TGraph("../data/Nantes/task1/A_el_0.3.txt","%lg %lg");
  }
  if(iT==12) {  // Nantes T = 0.4 GeV
    gr_add[0] = new TGraph("../data/Nantes/task1/A_el_ra_0.4.txt","%lg %lg");
    gr_add[1] = new TGraph("../data/Nantes/task1/A_el_0.4.txt","%lg %lg");
  }

  cout << " T_in = " << T_in << "\t index = " << iT << endl;
  int N_add_real = 0;
  if(iT==2 || iT==7 || iT==12) {
    for(int i=0;i<N_add;i++) {
      N_add_real++;
      cout << Name_add[i] << endl;
      gr_add[i]->Print();
      gr_add[i]->SetName(Name_add[i]);
      gr_add[i]->SetLineWidth(2);
      gr_add[i]->SetLineColor(Color_add[i]);
      gr_add[i]->SetLineStyle(Style_add[i]);
    }
  }
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,0,1000,800);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetErrorX(0.05);
  c1->SetFillColor(10);
  c1->SetFillStyle(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(0);
  c1->SetFrameFillColor(10);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  //  c1->SetLogy();
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetGridx(0);
  c1->SetGridy(0);
  c1->SetLeftMargin(0.13);
  c1->SetBottomMargin(0.14);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);

  double x1 = 0.0;
  double x2 = 40.0;
  double y1 = 0.;
  double y2 = 0.5*T_in/0.2;

  
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(505);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("p (GeV/c)");
  h0->GetXaxis()->SetTitleOffset(0.9);
  h0->GetXaxis()->SetTitleSize(0.07);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.045);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(52);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("A (1/fm)");
  h0->GetYaxis()->SetTitleOffset(0.8);
  h0->GetYaxis()->SetTitleSize(0.07);
  h0->GetYaxis()->SetLabelOffset(0.015);
  h0->GetYaxis()->SetLabelSize(0.045);
  h0->GetYaxis()->SetLabelFont(42);
  h0->GetYaxis()->SetTitleFont(52);
  h0->Draw("c");

  TLine *l1 = new TLine(x1,y1,x2,y1);
  l1->SetLineWidth(3);
  l1->Draw("same");
  TLine *l2 = new TLine(x1,y2,x2,y2);
  l2->SetLineWidth(3);
  l2->Draw("same");
  TLine *l3 = new TLine(x1,y1,x1,y2);
  l3->SetLineWidth(3);
  l3->Draw("same");
  TLine *l4 = new TLine(x2,y1,x2,y2);
  l4->SetLineWidth(3);
  l4->Draw("same");

  for(int i=0;i<N;i++) {
    gr[i][iT]->Draw("c");
  }

  for(int i=0;i<N_add_real;i++) {
    gr_add[i]->Draw("c");
  }
  
  TLegend *leg = new TLegend(0.68, 0.90-(N+N_add_real)*0.06, 0.94, 0.96);
  leg->SetFillColor(10);
  //   leg->SetFillStyle(10);
  leg->SetLineStyle(4000);
  leg->SetLineColor(10);
  leg->SetLineWidth(0.);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->AddEntry("",Form("T = %4.2f GeV",T_in),"");
  for(int i=0;i<N;i++) {
    leg->AddEntry(gr[i][iT],Name[i],"l");
  }
  for(int i=0;i<N_add_real;i++) {
    leg->AddEntry(gr_add[i],Name_add[i],"l");
  }
  leg->Draw();
  
  
  c1->Update();
  c1->SaveAs(Form("../fig/Q1c_A_%4.2f.pdf",T_in));
  c1->SaveAs(Form("../fig/Q1c_A_%4.2f.png",T_in));
  
}
