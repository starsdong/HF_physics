#include <stdio.h>
#include "iomanip.h"

void makeLcD0()
{
  gROOT->Reset();

  const Int_t NConfig = 4;
  const Int_t NMax = 5;
  const Int_t N[NConfig] = {3, 5, 4, 1}; // ALICE_pp, ALICE_pPb, STAR_AuAu
  const Char_t *ExpName[NConfig] = {"STAR","ALICE","ALICE","ALICE"};
  const Char_t *CollName[NConfig] = {"AuAu_10_80_200GeV","pp_7TeV","pPb_5p02TeV","PbPb_5p02TeV"};
  double x[NConfig][NMax], y[NConfig][NMax], ye[NConfig][NMax], yes_u[NConfig][NMax], yes_d[NConfig][NMax];
  TGraphErrors *gr[NConfig];

  ifstream inData;
  for(int i=0;i<NConfig;i++) {
    inData.open(Form("dat/%s_LcD0_%s.txt",ExpName[i],CollName[i]));
    for(int j=0;j<N[i];j++) {
      inData >> x[i][j] >> y[i][j] >> ye[i][j] >> yes_u[i][j] >> yes_d[i][j];
    }
    inData.close();
    gr[i] = new TGraphErrors(N[i], x[i], y[i], 0, ye[i]);
    cout << Form("dat/%s_LcD0_%s.txt",ExpName[i],CollName[i]) << endl;
    gr[i]->Print();
  }
  
  // Theory calculations
  // pythia
  TFile *fin = new TFile("root/pythia_D_ratio.root");
  TGraphErrors *gr_pythia_tmp = (TGraphErrors *)fin->Get("Ratio_Lc_D0");
  TGraph *gr_pythia = new TGraph(*gr_pythia_tmp);
  gr_pythia->SetLineWidth(2);
  gr_pythia->SetLineColor(16);

  TGraph *gr_pythia_7TeV = new TGraph("dat/PYTHIA_Lc_D0_pp_7TeV.txt","%lg %lg");
  TGraph *gr_pythia_7TeV_CR = new TGraph("dat/PYTHIACR_Lc_D0_pp_7TeV.txt","%lg %lg");
  TGraph *gr_Greco_LHC_1 = new TGraph("dat/Greco_LcD0_1_PbPb5p02TeV.txt","%lg %lg");
  TGraph *gr_Greco_LHC_2 = new TGraph("dat/Greco_LcD0_2_PbPb5p02TeV.txt","%lg %lg");
  TGraph *gr_ShaoSong_LHC_1 = new TGraph("dat/ShaoSong_LcD0_1_PbPb5p02TeV.txt","%lg %lg");
  TGraph *gr_ShaoSong_LHC_2 = new TGraph("dat/ShaoSong_LcD0_2_PbPb5p02TeV.txt","%lg %lg");
  /*
  const Int_t N_Greco = 14;
  Double_t pt_Greco[N_Greco], y_Greco[N_Greco], ye_Greco[N_Greco];
  inData.open("dat/LcD0_Greco_1407.5069.txt");
  for(int i=0;i<N_Greco;i++) {
    double a, b, c;
    inData >> a >> b >> c;
    pt_Greco[i] = a;
    y_Greco[i] = (b+c)/2.;
    ye_Greco[i] = fabs(b-c)/2.;
  }
  inData.close();
  TGraphErrors *gr_Greco = new TGraphErrors(N_Greco, pt_Greco, y_Greco, 0, ye_Greco);
  gr_Greco->SetFillColor(16);
  gr_Greco->SetLineColor(16);
  */
  TGraph *gr_Greco_1 = new TGraph("dat/Greco_LcD0_1_AuAu200GeV_20_50.dat","%lg %lg");
  gr_Greco_1->SetLineWidth(2);
  gr_Greco_1->SetLineStyle(2);
  gr_Greco_1->SetLineColor(4);
  TGraph *gr_Greco_2 = new TGraph("dat/Greco_LcD0_2_AuAu200GeV_20_50.dat","%lg %lg");
  gr_Greco_2->SetLineWidth(2);
  gr_Greco_2->SetLineStyle(4);
  gr_Greco_2->SetLineColor(4);
  
  
  const Int_t N_Ko = 12;
  Double_t pt_Ko[N_Ko], y1_Ko[N_Ko], y2_Ko[N_Ko], y3_Ko[N_Ko];
  inData.open("dat/LcD0_Ko_0901.1382.txt");
  for(int i=0;i<N_Ko;i++) {
    inData >> pt_Ko[i] >> y1_Ko[i] >> y2_Ko[i] >> y3_Ko[i];
  }
  inData.close();
  TGraph *gr_Ko_1 = new TGraph(N_Ko, pt_Ko, y1_Ko);
  gr_Ko_1->SetLineWidth(2);
  gr_Ko_1->SetLineColor(2);
  gr_Ko_1->SetLineStyle(3);
  TGraph *gr_Ko_2 = new TGraph(N_Ko, pt_Ko, y2_Ko);
  gr_Ko_2->SetLineWidth(2);
  gr_Ko_2->SetLineColor(2);
  gr_Ko_2->SetLineStyle(2);
  TGraph *gr_Ko_3 = new TGraph(N_Ko, pt_Ko, y3_Ko);
  gr_Ko_3->SetLineWidth(2);
  gr_Ko_3->SetLineColor(2);
  gr_Ko_3->SetLineStyle(4);

  TGraph *gr_Tsinghua_1 = new TGraph("dat/Tsinghua_LcD0_1_AuAu200GeV_10_80.txt","%lg %lg");
  gr_Tsinghua_1->SetLineWidth(2);
  gr_Tsinghua_1->SetLineStyle(3);
  gr_Tsinghua_1->SetLineColor(8);
  
  TGraph *gr_Tsinghua_2 = new TGraph("dat/Tsinghua_LcD0_2_AuAu200GeV_10_80.txt","%lg %lg");
  gr_Tsinghua_2->SetLineWidth(2);
  gr_Tsinghua_2->SetLineStyle(3);
  gr_Tsinghua_2->SetLineColor(8);

  TCanvas *c1 = new TCanvas("c1", "c1",0,0,1200,800);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);

  TPad *p1 = new TPad("p1","p1",0.0,0.1,0.54,1.0);
  p1->SetFillColor(10);
  p1->SetFillStyle(0);
  p1->SetBorderMode(0);
  p1->SetBorderSize(0);
  p1->SetFrameFillColor(10);
  p1->SetFrameFillStyle(0);
  p1->SetFrameBorderMode(0);
  p1->SetLeftMargin(0.18);
  p1->SetRightMargin(0.001);
  p1->SetTopMargin(0.03);
  p1->SetBottomMargin(0.05);
  //  p1->SetLogy();
  p1->SetTickx();
  p1->SetTicky();
  p1->Draw();
  p1->cd();


  double x1 = 0.01;
  double x2 = 7.99;
  double y1 = 0.001;
  double y2 = 3.1;
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(208);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
  h0->GetXaxis()->SetTitleOffset(99.);
  h0->GetXaxis()->SetTitleSize(0.07);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.05);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("(#Lambda_{c}^{+}+#bar{#Lambda_{c}}^{-})/(D^{0}+#bar{D}^{0})");
  h0->GetYaxis()->SetTitleOffset(1.0);
  h0->GetYaxis()->SetTitleSize(0.07);
  h0->GetYaxis()->SetLabelOffset(0.018);
  h0->GetYaxis()->SetLabelSize(0.05);
  h0->GetYaxis()->SetLabelFont(42);
  h0->GetYaxis()->SetTitleFont(42);
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


  gr_pythia->SetFillColor(16);
  gr_pythia->SetLineWidth(2);
  gr_pythia->SetLineStyle(2);
  gr_pythia->SetLineColor(1);
  gr_pythia->Draw("c");

  
  gr_Greco_1->Draw("c");
  //  gr_Greco_2->Draw("c");
  //  gr_Ko_1->Draw("c");
  gr_Ko_2->Draw("c");
  gr_Ko_3->Draw("c"); // pythia

  gr_Tsinghua_1->Draw("c");


  /*
  TLatex *tex = new TLatex(3, 0.32, "Greco");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  tex->Draw("same");

  TLatex *tex = new TLatex(1, 0.78, "Ko: three-quark");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  tex->Draw("same");

  TLatex *tex = new TLatex(2, 1.3, "Ko: di-quark");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  tex->Draw("same");
  */
  
  TLine *la = new TLine(0.2, 0.24, 1.5, 0.24);
  la->SetLineWidth(5);
  la->SetLineColor(18);
  //  la->Draw("same");

  TLatex *tex = new TLatex(0.5, 0.26, "SHM");
  tex->SetTextFont(12);
  tex->SetTextSize(0.06);
  //  tex->Draw("same");

  // plotting the data points
  const Int_t kStyle[NConfig] = {20, 20, 24, 20};
  const Int_t kColor[NConfig] = {1, 2, 4, 1};
  const double xo = fabs(x2-x1)/60.;
  const double yo = fabs(y2-y1)/80.;
  for(int i=0;i<1;i++) {  // STAR

    for(int j=0;j<N[i];j++) { 
      double x1 = x[i][j] - xo;
      double x2 = x[i][j] + xo;
      double y1 = y[i][j] - yes_d[i][j];
      double y2 = y[i][j] + yes_u[i][j];
      
      TLine *la = new TLine(x1, y1, x1, y1+yo);
      la->SetLineColor(kColor[i]);
      la->SetLineWidth(1);
      la->Draw("same");
      TLine *lb = new TLine(x2, y1, x2, y1+yo);
      lb->SetLineColor(kColor[i]);
      lb->SetLineWidth(1);
      lb->Draw("same");
      TLine *lc = new TLine(x1, y2, x1, y2-yo);
      lc->SetLineColor(kColor[i]);
      lc->SetLineWidth(1);
      lc->Draw("same");
      TLine *ld = new TLine(x2, y2, x2, y2-yo);
      ld->SetLineColor(kColor[i]);
      ld->SetLineWidth(1);
      ld->Draw("same");
      TLine *le = new TLine(x1, y1, x2, y1);
      le->SetLineColor(kColor[i]);
      le->SetLineWidth(2);
      le->Draw("same");
      TLine *lf = new TLine(x1, y2, x2, y2);
      lf->SetLineColor(kColor[i]);
      lf->SetLineWidth(2);
      lf->Draw("same");
    }
    gr[i]->SetMarkerStyle(kStyle[i]);
    gr[i]->SetMarkerColor(kColor[i]);
    gr[i]->SetMarkerSize(2.2);
    gr[i]->SetLineColor(kColor[i]);
    gr[i]->SetLineWidth(2);
    gr[i]->Draw("p");
  }

  TLatex *tex = new TLatex(2.0, 3.1*0.92, "STAR @ RHIC");
  tex->SetTextFont(22);
  tex->SetTextSize(0.055);
  tex->Draw("same");
  
  TLatex *tex = new TLatex(4.5, 1.06, "10-80%");
  tex->SetTextFont(32);
  tex->SetTextSize(0.036);
  tex->Draw("same");

  TLegend *leg = new TLegend(0.22, 0.8, 0.54, 0.86);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.037);
   leg->AddEntry(gr[0], " Au+Au@200GeV", "pl");
   leg->Draw();

   TLegend *leg = new TLegend(0.6, 0.56, 0.94, 0.86);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.037);
   leg->AddEntry(gr_Greco_1,"Greco: 20-50%","l");
   leg->AddEntry(gr_Ko_3,"Ko: di-quark 0-5%","l");
   leg->AddEntry(gr_Ko_2,"Ko: 3-quark 0-5%","l");
   leg->AddEntry(gr_Tsinghua_1,"Tsinghua: 10-80%","l");
   leg->AddEntry(gr_pythia,"PYTHIA6","l");   
   leg->Draw();

   p1->Modified();
   c1->cd();
   c1->Update();
   
  TPad *p2 = new TPad("p2","p2",0.54,0.1,1.0,1.0);
  p2->SetFillColor(10);
  p2->SetFillStyle(0);
  p2->SetBorderMode(0);
  p2->SetBorderSize(0);
  p2->SetFrameFillColor(10);
  p2->SetFrameFillStyle(0);
  p2->SetFrameBorderMode(0);
  p2->SetLeftMargin(0.001);
  p2->SetRightMargin(0.03);
  p2->SetTopMargin(0.03);
  p2->SetBottomMargin(0.05);
  //  p2->SetLogy();
  p2->SetTickx();
  p2->SetTicky();
  p2->Draw();
  p2->cd();


  double x1 = 0.01;
  double x2 = 11.99;
  double y1 = 0.001;
  double y2 = 3.1;
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(208);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
  h0->GetXaxis()->SetTitleOffset(999.);
  h0->GetXaxis()->SetTitleSize(0.06);
  h0->GetXaxis()->SetLabelOffset(-0.003);
  h0->GetXaxis()->SetLabelSize(0.06);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("(#Lambda_{c}^{+}+#overline{#Lambda_{c}}^{-})/(D^{0}+#overline{D}^0)");
  h0->GetYaxis()->SetTitleOffset(999.);
  h0->GetYaxis()->SetTitleSize(0.07);
  h0->GetYaxis()->SetLabelOffset(999.);
  h0->GetYaxis()->SetLabelSize(0.06);
  h0->GetYaxis()->SetLabelFont(42);
  h0->GetYaxis()->SetTitleFont(42);
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


  gr_pythia_7TeV->SetLineColor(1);
  gr_pythia_7TeV->SetLineWidth(2);
  gr_pythia_7TeV->SetLineStyle(2);
  gr_pythia_7TeV->Draw("c");
  
  gr_pythia_7TeV_CR->SetLineColor(1);
  gr_pythia_7TeV_CR->SetLineWidth(2);
  gr_pythia_7TeV_CR->SetLineStyle(4);
  gr_pythia_7TeV_CR->Draw("c");

  gr_Greco_LHC_1->SetLineColor(4);
  gr_Greco_LHC_1->SetLineWidth(2);
  gr_Greco_LHC_1->SetLineStyle(2);
  gr_Greco_LHC_1->Draw("c");

  gr_Greco_LHC_2->SetLineColor(4);
  gr_Greco_LHC_2->SetLineWidth(2);
  gr_Greco_LHC_2->SetLineStyle(4);
  //  gr_Greco_LHC_2->Draw("c");

  gr_ShaoSong_LHC_1->SetLineColor(2);
  gr_ShaoSong_LHC_1->SetLineWidth(2);
  gr_ShaoSong_LHC_1->SetLineStyle(2);
  gr_ShaoSong_LHC_1->Draw("c");
  
  gr_ShaoSong_LHC_2->SetLineColor(2);
  gr_ShaoSong_LHC_2->SetLineWidth(2);
  gr_ShaoSong_LHC_2->SetLineStyle(4);
  gr_ShaoSong_LHC_2->Draw("c");

  // plotting the data points
  const Int_t kStyle[NConfig] = {20, 20, 24, 20};
  const Int_t kColor[NConfig] = {1, 2, 4, 1};
  const double xo = fabs(x2-x1)/60.;
  const double yo = fabs(y2-y1)/80.;
  for(int i=1;i<NConfig;i++) {

    for(int j=0;j<N[i];j++) {
      double x1 = x[i][j] - xo;
      double x2 = x[i][j] + xo;
      double y1 = y[i][j] - yes_d[i][j];
      double y2 = y[i][j] + yes_u[i][j];
      
      TLine *la = new TLine(x1, y1, x1, y1+yo);
      la->SetLineColor(kColor[i]);
      la->SetLineWidth(1);
      la->Draw("same");
      TLine *lb = new TLine(x2, y1, x2, y1+yo);
      lb->SetLineColor(kColor[i]);
      lb->SetLineWidth(1);
      lb->Draw("same");
      TLine *lc = new TLine(x1, y2, x1, y2-yo);
      lc->SetLineColor(kColor[i]);
      lc->SetLineWidth(1);
      lc->Draw("same");
      TLine *ld = new TLine(x2, y2, x2, y2-yo);
      ld->SetLineColor(kColor[i]);
      ld->SetLineWidth(1);
      ld->Draw("same");
      TLine *le = new TLine(x1, y1, x2, y1);
      le->SetLineColor(kColor[i]);
      le->SetLineWidth(2);
      le->Draw("same");
      TLine *lf = new TLine(x1, y2, x2, y2);
      lf->SetLineColor(kColor[i]);
      lf->SetLineWidth(2);
      lf->Draw("same");
    }
    gr[i]->SetMarkerStyle(kStyle[i]);
    gr[i]->SetMarkerColor(kColor[i]);
    gr[i]->SetMarkerSize(2.0);
    gr[i]->SetLineColor(kColor[i]);
    gr[i]->SetLineWidth(2);
    gr[i]->Draw("p");
  }
  
  TLatex *tex = new TLatex(3.0, 3.1*0.92, "ALICE @ LHC");
  tex->SetTextFont(22);
  tex->SetTextSize(0.065);
  tex->Draw("same");

  TLatex *tex = new TLatex(9.2, 1.3, "0-80%");
  tex->SetTextFont(32);
  tex->SetTextSize(0.045);
  tex->Draw("same");

   TLegend *leg = new TLegend(0.05, 0.68, 0.45, 0.86);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.042);
   leg->AddEntry(gr[3], " Pb+Pb@5.02TeV", "pl");
   leg->AddEntry(gr[2], " p+Pb@5.02TeV", "pl");
   leg->AddEntry(gr[1], " p+p@7TeV", "pl");
   leg->Draw();

   TLegend *leg = new TLegend(0.5, 0.56, 0.94, 0.86);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.042);
   leg->AddEntry(gr_Greco_LHC_1,"Greco: frag+coal","l");
   leg->AddEntry(gr_ShaoSong_LHC_1,"Shao: R_{B/M}=0.425","l");
   leg->AddEntry(gr_ShaoSong_LHC_2,"Shao: R_{B/M}=1.2","l");
   leg->AddEntry(gr_pythia_7TeV_CR,"PYTHIA (CR)","l");   
   leg->AddEntry(gr_pythia_7TeV,"PYTHIA","l");   
   leg->Draw();


   p2->Modified();
   c1->cd();
   c1->Update();
  
  c1->Update();
  c1->cd();

  TLatex *tex = new TLatex(0.3,0.04, "Transverse Momentum (GeV/c)");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->Draw("same");

  /*
  TPad *p3 = new TPad("p3","p3",0.0,0.0,1.0,0.1);
  p2->SetFillColor(10);
  p2->SetFillStyle(0);
  p2->SetBorderMode(0);
  p2->SetBorderSize(0);
  p2->SetFrameFillColor(10);
  p2->SetFrameFillStyle(0);
  p2->SetFrameBorderMode(0);
  p2->SetLeftMargin(0.001);
  p2->SetRightMargin(0.03);
  p2->SetTopMargin(0.03);
  p2->SetBottomMargin(0.05);
  //  p2->SetLogy();
  p2->SetTickx();
  p2->SetTicky();
  p2->Draw();
  p2->cd();
  */
  
  c1->SaveAs("fig/LcD0Ratio.pdf");
  c1->SaveAs("fig/LcD0Ratio.png");
  
  
}
