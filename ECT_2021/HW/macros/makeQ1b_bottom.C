#include "stdio.h"
#include <iomanip.h>

void makeQ1b_bottom(const float T_in = 0.3)
{
  gROOT->Reset();

  const Int_t N = 5;
  const Int_t Ng = 1;
  const Float_t T_min = 0.16;
  const Float_t T_max = 0.60;
  const Float_t p_min = 0;
  const Float_t p_max = 40.0;
  const Int_t NTMax = 23; // T: 0.16-0.60, 0.02 per bin
  const Int_t NPMax = 201;  // p:  0-40, 0.2 per bin

  Int_t NT[N] = {23,22,22,23,23};
  Int_t NP[N] = {201,80,200,151,201};
  const Char_t *FileName[N] = {"../data/PHSD/bottom/homework1b-bottom-phsd.dat",
			       "",
			       "",
			       "",
			       ""};
  const Char_t *Name[N] = {"PHSD","CUJET","Duke","TAMU","Catania"};
  const Int_t Color[N] = {kBlack, kRed, kGreen+2, kBlue, kOrange+1};
  const Int_t Style[N] = {1, 2, 3, 9, 5};

  const Int_t N_add = 2;
  TGraph *gr_add[10];
  const Char_t *Name_add[N_add] = {"Nantes","DAB-MOD"};
  const Int_t Color_add[N_add] = {kMagenta+1, kAzure+1};
  const Int_t Style_add[N_add] = {7, 4};
  
  TGraph *gr[N][NTMax];  // vs. p
  Float_t T[N][NTMax];
  Float_t p[N][NPMax];
  Float_t A[N][NTMax][NPMax];
  Float_t B[N][NTMax][NPMax];
  Float_t A0[N][NTMax]; // A0 for some models
  cout << " Read in data.... " << endl;
  ifstream inData;
  for(int i=0;i<N;i++) {
    //
    if(i==1 || i==2 || i==3 || i==4) continue;
    inData.open(FileName[i]);
    switch (i) {
    case 0:    // PHSD
      for(int j=0;j<NT[i];j++) {
	for(int k=0;k<NP[i];k++) {
	  inData >> T[i][j] >> p[i][k] >> A[i][j][k];
	}	
      }
      break;
    case 1:   // CUJET - unnormalized
      for(int k=0;k<NP[i];k++) {
	for(int j=0;j<NT[i];j++) {
	  inData >> p[i][k] >> T[i][j] >> A[i][j][k];
	  if(k==0) A0[i][j] = A[i][j][0];
	}	
      }
      for(int k=0;k<NP[i];k++) {
	for(int j=0;j<NT[i];j++) { // normalization
	  A[i][j][k] /= A0[i][j];
	}
      }
      break;
    case 2:    // Duke
      for(int k=0;k<NP[i];k++) {
	for(int j=0;j<NT[i];j++) {
	  inData >> p[i][k] >> T[i][j] >> A[i][j][k];
	}	
      }
      break;
    case 3:    // TAMU
      for(int j=0;j<NT[i];j++) {
	for(int k=0;k<NP[i];k++) {
	  inData >> T[i][j] >> p[i][k] >> A[i][j][k];
	}	
      }
      break;
    case 4:    // Catania
      for(int j=0;j<NT[i];j++) {
	for(int k=0;k<NP[i];k++) {
	  inData >> T[i][j] >> p[i][k] >> A[i][j][k] >> B[i][j][k];
	  if(k==0) A0[i][j] = A[i][j][0];
	}	
      }
      for(int j=0;j<NT[i];j++) { // normalization
	for(int k=0;k<NP[i];k++) {
	  A[i][j][k] /= A0[i][j];
	}
      }
      break;
    default:  //
      break;
    }
    inData.close();
  }

  for(int i=0;i<N;i++) {
    for(int j=0;j<NT[i];j++) {
      gr[i][j] = new TGraph(NP[i], p[i], A[i][j]);
      gr[i][j]->SetName(Form("%s_%4.2f",Name[i],float(T[i][j]+0.0001)));
      gr[i][j]->SetLineWidth(2);
      gr[i][j]->SetLineColor(Color[i]);
      gr[i][j]->SetLineStyle(Style[i]);
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
    gr_add[0] = new TGraph("../data/Nantes/task1/norm_drag_b_0.2.txt","%lg %lg");
  }
  if(iT==7) {  // Nantes T = 0.3 GeV
    gr_add[0] = new TGraph("../data/Nantes/task1/norm_drag_b_0.3.txt","%lg %lg");
  }
  if(iT==12) {  // Nantes T = 0.4 GeV
    gr_add[0] = new TGraph("../data/Nantes/task1/norm_drag_b_0.4.txt","%lg %lg");
  }
  if(gr_add[0]) {
    gr_add[0]->SetName("Nantes");
    gr_add[0]->SetLineWidth(2);
    gr_add[0]->SetLineColor(Color_add[0]);
    gr_add[0]->SetLineStyle(Style_add[0]);
  }
  // DAB-MOD
  TF1 *f1 = new TF1("f1","sqrt([0]*[0]/(x*x+[0]*[0]))",0.,40.);
  f1->SetParameter(0,4.5);
  double p_tmp[NPMax], A_tmp[NPMax];
  for(int k=0;k<NPMax;k++) {
    p_tmp[k] = k*(p_max-p_min)/(NPMax-1)+p_min;
    A_tmp[k] = f1->Eval(p_tmp[k]);
  }
  gr_add[1] = new TGraph(NPMax, p_tmp, A_tmp);
  gr_add[1]->SetName("DAB-MOD");
  gr_add[1]->SetLineWidth(2);
  gr_add[1]->SetLineColor(Color_add[1]);
  gr_add[1]->SetLineStyle(Style_add[1]);    
  Int_t N_add_exit = 0;
  for(int i=0;i<N_add;i++) {
    if(gr_add[i]) {
      gr_add[i]->Print();
      N_add_exit++;
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
  double y2 = 1.2;

  
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
  h0->GetYaxis()->SetTitle("A(p;T)/A(p=0;T)");
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
    if(i==1 || i==2 || i==3 || i==4) continue;
    gr[i][iT]->Draw("c");
  }
  for(int i=0;i<N_add;i++) {
    if(gr_add[i]) gr_add[i]->Draw("c");
  }

  TLegend *leg = new TLegend(0.68, 0.88-(Ng+N_add_exit)*0.06, 0.94, 0.94);
  leg->SetFillColor(10);
  //   leg->SetFillStyle(10);
  leg->SetLineStyle(4000);
  leg->SetLineColor(10);
  leg->SetLineWidth(0.);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->AddEntry("",Form("T = %4.2f GeV",T_in),"");
  for(int i=0;i<N;i++) {
    if(i==1 || i==2 || i==3 || i==4) continue;
    leg->AddEntry(gr[i][iT],Name[i],"l");
  }
  for(int i=0;i<N_add;i++) {
    if(gr_add[i]) leg->AddEntry(gr_add[i],Name_add[i],"l");
  }
  leg->Draw();
  
  
  c1->Update();
  c1->SaveAs(Form("../fig/Q1b_bottom_A_%4.2f.pdf",T_in));
  c1->SaveAs(Form("../fig/Q1b_bottom_A_%4.2f.png",T_in));
  
}
