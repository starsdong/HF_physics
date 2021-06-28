#include <stdio.h>
#include "iomanip.h"

void make_DHQ_092019()
{
  gROOT->Reset();

  const Double_t twoPi = 3.1415927*2.0;

  const Int_t n_star = 1;
  const Double_t x_star[n_star] = {2.1};
  const Double_t y_star[n_star] = {2.0};
  const Double_t ye_star[n_star] = {1.0};

  TGraphErrors *gr_star = new TGraphErrors(n_star, x_star, y_star, 0, ye_star);
  
  const Int_t n_txt1 = 12;
  const Double_t x_txt1[n_txt1] = {0.75, 0.67, 2.0, 1.7, 1.6, 1.6, 2.1, 2.02, 2.0, 1.6, 2.25, 2.1};
  const Double_t y_txt1[n_txt1] = {14.5, 11.8, 32.5, 32.2, 21, 7.6, 10., 12.0, 7.5, 2.5, 2.8, 5.5};
  const Double_t angle_txt1[n_txt1] = {-68, -70., 5, 30, 7, 25, 16, 28, 21, 6, 0., 12.0};
  const Char_t *tex_txt1[n_txt1] = {"D-meson (TAMU)", "D-meson (Ozvenchuk)", "pQCD LO #alpha_{S}=0.4", "pQCD LO #alpha_{s}(T)", "T-Matrix V=F", "T-Matrix V=U", "PHSD", "QPM (Catania) - LV", "QPM (Catania) - BM", "MC@sHQ", "AdS/CFT", "Duke (Bayesian)"};
  const Int_t kColor[n_txt1] = {kBlue, kRed, kBlack, kBlack, kBlack, kBlack, kMagenta, kRed, kBlue, kBlack, kBlack, kCyan+2};

  const Int_t n_txt2 = 3;
  const Char_t *tex_txt2[n_txt2] = {"Banerjee", "Ding", "Kaczmarek"};
  
  TGraph *gr_pQCD_LO = new TGraph("/Users/starsdong/work/datapoints/D_HQ/pQCD_LO.txt","%lg %lg");
  TGraph *gr_HRG = new TGraph("/Users/starsdong/work/datapoints/D_HQ/HRG.txt","%lg %lg");
  TGraph *gr_DQPM = new TGraph("/Users/starsdong/work/datapoints/D_HQ/DQPM.txt","%lg %lg");

  TGraph *gr_pQCD_LO_04 = new TGraph("/Users/starsdong/work/datapoints/D_HQ/LOpQCD_alpha_04.txt","%lg %lg");
  TGraph *gr_pQCD_LO_alphaT = new TGraph("/Users/starsdong/work/datapoints/D_HQ/LOpQCD_alphaT.txt","%lg %lg");
  TGraph *gr_QPM_Catania_LV = new TGraph("/Users/starsdong/work/datapoints/D_HQ/QPM_Catania_LV.txt","%lg %lg");
  TGraph *gr_QPM_Catania_BM = new TGraph("/Users/starsdong/work/datapoints/D_HQ/QPM_Catania_BM.txt","%lg %lg");
  TGraph *gr_TAMU_LV = new TGraph("/Users/starsdong/work/datapoints/D_HQ/T-Matrix_LV.txt","%lg %lg");
  TGraph *gr_PHSD = new TGraph("/Users/starsdong/work/datapoints/D_HQ/PHSD.txt","%lg %lg");
  TGraph *gr_Dmeson_TAMU = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Dmeson_TAMU.txt","%lg %lg");
  TGraph *gr_Dmeson_Oz = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Dmeson_Ozvenchuk.txt","%lg %lg");
  TGraph *gr_Duke_0 = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Duke_0.txt","%lg %lg");
  TGraph *gr_Duke_low = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Duke_low.txt","%lg %lg");
  TGraph *gr_Duke_high = new TGraph("/Users/starsdong/work/datapoints/D_HQ/Duke_high.txt","%lg %lg");
  double x_Duke[100], y_Duke[100], ye_low_Duke[100], ye_high_Duke[100];
  for(int i=0;i<gr_Duke_0->GetN();i++) {
    x_Duke[i] = gr_Duke_0->GetX()[i];
    y_Duke[i] = gr_Duke_0->GetY()[i];
    ye_low_Duke[i] = fabs(gr_Duke_low->Eval(x_Duke[i]) - gr_Duke_0->GetY()[i]);
    ye_high_Duke[i] = fabs(gr_Duke_high->Eval(x_Duke[i]) - gr_Duke_0->GetY()[i]);
  }
  TGraphAsymmErrors *gr_Duke = new TGraphAsymmErrors(gr_Duke_0->GetN(), x_Duke, y_Duke, 0, 0, ye_low_Duke, ye_high_Duke);
  
  
  const Double_t D_AdsCFT_min = 2.5;
  const Double_t D_AdsCFT_max = 4.2;
  const Double_t D_AdsCFT = (D_AdsCFT_min+D_AdsCFT_max)/2.;
  const Double_t D_AdsCFT_e = fabs(D_AdsCFT_min-D_AdsCFT_max)/2.;

  const Int_t n_Kac = 1;
  const Double_t x_Kac[n_Kac] = {1.4};
  const Double_t y_Kac[n_Kac] = {5.18};
  const Double_t ye_Kac[n_Kac] = {1.16};
  TGraphErrors *gr_L_Kac = new TGraphErrors(n_Kac, x_Kac, y_Kac, 0, ye_Kac);
  
  ifstream inData;
  inData.open("/Users/starsdong/work/datapoints/D_HQ/SUBATECH.txt");
  const Int_t n_SUB = 6;
  //  const Int_t n_SUB = 8;
  double x_SUB[n_SUB], y_SUB[n_SUB], ye_SUB[n_SUB];
  for(int i=0;i<n_SUB;i++) {
    double a, b, c;
    inData >> a >> b >> c;
    x_SUB[i] = a;
    y_SUB[i] = (b+c)/2.;
    ye_SUB[i] = fabs(b-c)/2.;
  }
  TGraphErrors *gr_SUB = new TGraphErrors(n_SUB, x_SUB, y_SUB, 0, ye_SUB);
  inData.close();

  inData.open("/Users/starsdong/work/datapoints/D_HQ/T-Matrix_U.txt");
  const Int_t n_T_U = 11;
  double x_T_U[n_T_U], y_T_U[n_T_U], ye_T_U[n_T_U];
  for(int i=0;i<n_T_U;i++) {
    double a, b, c;
    inData >> a >> b >> c;
    x_T_U[i] = a;
    y_T_U[i] = (b+c)/2.;
    ye_T_U[i] = fabs(b-c)/2.;
  }
  TGraphErrors *gr_T_U = new TGraphErrors(n_T_U, x_T_U, y_T_U, 0, ye_T_U);
  inData.close();

  inData.open("/Users/starsdong/work/datapoints/D_HQ/T-Matrix_F.txt");
  const Int_t n_T_F = 11;
  double x_T_F[n_T_F], y_T_F[n_T_F], ye_T_F[n_T_F];
  for(int i=0;i<n_T_F;i++) {
    double a, b, c;
    inData >> a >> b >> c;
    x_T_F[i] = a;
    y_T_F[i] = (b+c)/2.;
    ye_T_F[i] = fabs(b-c)/2.;
  }
  TGraphErrors *gr_T_F = new TGraphErrors(n_T_F, x_T_F, y_T_F, 0, ye_T_F);
  inData.close();
  
  inData.open("/Users/starsdong/work/datapoints/D_HQ/LQCD_Ding.txt");
  const Int_t n_L_Ding = 3;
  double x_L_Ding[n_L_Ding], xe_L_Ding[n_L_Ding], y_L_Ding[n_L_Ding], ye_L_Ding[n_L_Ding], yesL_L_Ding[n_L_Ding], yesU_L_Ding[n_L_Ding];
  double yeL_L_Ding[n_L_Ding], yeU_L_Ding[n_L_Ding];  // stat + sys
  for(int i=0;i<n_L_Ding;i++) {
    inData >> x_L_Ding[i] >> y_L_Ding[i] >> ye_L_Ding[i] >> yesL_L_Ding[i] >> yesU_L_Ding[i];
    xe_L_Ding[i] = 0.01;
    yeL_L_Ding[i] = sqrt(ye_L_Ding[i]**2+yesL_L_Ding[i]**2);
    yeU_L_Ding[i] = sqrt(ye_L_Ding[i]**2+yesU_L_Ding[i]**2);
  }
  inData.close();
  TGraphErrors *gr_L_Ding = new TGraphErrors(n_L_Ding, x_L_Ding, y_L_Ding, 0, ye_L_Ding);
  TGraphAsymmErrors *gr_L_Ding_sys = new TGraphAsymmErrors(n_L_Ding, x_L_Ding, y_L_Ding, xe_L_Ding, xe_L_Ding, yesL_L_Ding, yesU_L_Ding);
  TGraphAsymmErrors *gr_L_Ding_tot = new TGraphAsymmErrors(n_L_Ding, x_L_Ding, y_L_Ding, 0, 0, yeL_L_Ding, yeU_L_Ding);

  inData.open("/Users/starsdong/work/datapoints/D_HQ/LQCD_Banerjee.txt");
  const Int_t n_L_Banerjee = 5;
  double x_L_Banerjee[n_L_Banerjee], xe_L_Banerjee[n_L_Banerjee], y_L_Banerjee[n_L_Banerjee], ye_L_Banerjee[n_L_Banerjee], yesL_L_Banerjee[n_L_Banerjee], yesU_L_Banerjee[n_L_Banerjee];
  double yeL_L_Banerjee[n_L_Banerjee], yeU_L_Banerjee[n_L_Banerjee];  // stat + sys
  for(int i=0;i<n_L_Banerjee;i++) {
    inData >> x_L_Banerjee[i] >> y_L_Banerjee[i] >> ye_L_Banerjee[i] >> yesL_L_Banerjee[i] >> yesU_L_Banerjee[i];
    y_L_Banerjee[i] *= twoPi;
    ye_L_Banerjee[i] *= twoPi;
    yesL_L_Banerjee[i] *= twoPi;
    yesU_L_Banerjee[i] *= twoPi;
    xe_L_Banerjee[i] = 0.01;
    yeL_L_Banerjee[i] = sqrt(ye_L_Banerjee[i]**2+yesL_L_Banerjee[i]**2);
    yeU_L_Banerjee[i] = sqrt(ye_L_Banerjee[i]**2+yesU_L_Banerjee[i]**2);
  }
  inData.close();
  TGraphErrors *gr_L_Banerjee = new TGraphErrors(n_L_Banerjee, x_L_Banerjee, y_L_Banerjee, 0, ye_L_Banerjee);
  TGraphAsymmErrors *gr_L_Banerjee_sys = new TGraphAsymmErrors(n_L_Banerjee, x_L_Banerjee, y_L_Banerjee, xe_L_Banerjee, xe_L_Banerjee, yesL_L_Banerjee, yesU_L_Banerjee);
  TGraphAsymmErrors *gr_L_Banerjee_tot = new TGraphAsymmErrors(n_L_Banerjee, x_L_Banerjee, y_L_Banerjee, 0, 0, yeL_L_Banerjee, yeU_L_Banerjee);

  

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

  double x1 = 0.501;
  double x2_sep = 2.48;
  double x2 = 2.48;
  double y1 = 0.;
  double y2 = 22.;

  const Int_t n_AdsCFT = 2.;
  const Double_t x_AdsCFT[n_AdsCFT] = {1., x2};
  const Double_t y_AdsCFT[n_AdsCFT] = {D_AdsCFT, D_AdsCFT};
  const Double_t ye_AdsCFT[n_AdsCFT] = {D_AdsCFT_e, D_AdsCFT_e};
  TGraphErrors *gr_AdsCFT = new TGraphErrors(n_AdsCFT, x_AdsCFT, y_AdsCFT, 0, ye_AdsCFT);

  
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(505);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("T/T_{pc}");
  h0->GetXaxis()->SetTitleOffset(0.9);
  h0->GetXaxis()->SetTitleSize(0.07);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.045);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(52);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("2#piTD_{s}");
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

  TLine *l5 = new TLine(x2_sep,y1,x2_sep,y2);
  l5->SetLineWidth(1);
  l5->Draw("same");

  gr_HRG->SetLineWidth(2);
  gr_HRG->SetLineStyle(4);
  gr_HRG->SetLineColor(4);
  //  gr_HRG->Draw("c");

  gr_Duke->SetFillColorAlpha(5,0.35);
  gr_Duke->SetLineColorAlpha(5,0.35);
  gr_Duke->Draw("e3");
  
  gr_pQCD_LO->SetLineWidth(2);
  gr_pQCD_LO->SetLineStyle(2);
  gr_pQCD_LO->SetLineColor(1);
  //  gr_pQCD_LO->Draw("c");

  gr_AdsCFT->SetLineColor(16);
  gr_AdsCFT->SetFillColor(16);
  gr_AdsCFT->Draw("e3");
  
  gr_SUB->SetLineColor(13);
  gr_SUB->SetFillColor(13);
  //  gr_SUB->SetFillColorAlpha(13,0.5);
  gr_SUB->Draw("e3");

  gr_DQPM->SetLineColor(7);
  gr_DQPM->SetLineStyle(4);
  gr_DQPM->SetLineWidth(4);
  //  gr_DQPM->Draw("c");

  gr_T_F->SetLineColor(3);
  gr_T_F->SetFillColor(3);
  //  gr_T_F->Draw("e3");

  gr_T_U->SetLineColor(8);
  gr_T_U->SetFillColor(8);
  gr_T_U->Draw("e3");


  gr_pQCD_LO_04->SetLineStyle(2);
  gr_pQCD_LO_04->SetLineColor(kBlack);
  gr_pQCD_LO_04->SetLineWidth(4);
  //  gr_pQCD_LO_04->Draw("l");

  gr_pQCD_LO_alphaT->SetLineStyle(3);
  gr_pQCD_LO_alphaT->SetLineColor(kBlack);
  gr_pQCD_LO_alphaT->SetLineWidth(4);
  //  gr_pQCD_LO_alphaT->Draw("c");
  
  gr_PHSD->SetLineColor(kMagenta);
  gr_PHSD->SetLineWidth(4);
  gr_PHSD->SetLineStyle(2);
  gr_PHSD->Draw("c");

  gr_Duke_0->SetLineColor(kCyan+2);
  gr_Duke_0->SetLineWidth(4);
  gr_Duke_0->SetLineStyle(4);
  gr_Duke_0->Draw("c");
  

  gr_Dmeson_TAMU->SetLineColor(kBlue);
  gr_Dmeson_TAMU->SetLineWidth(4);
  gr_Dmeson_TAMU->SetLineStyle(2);
  gr_Dmeson_TAMU->Draw("c");

  gr_Dmeson_Oz->SetLineColor(kRed);
  gr_Dmeson_Oz->SetLineWidth(4);
  gr_Dmeson_Oz->SetLineStyle(2);
  gr_Dmeson_Oz->Draw("c");

  gr_QPM_Catania_LV->SetLineColor(kRed);
  gr_QPM_Catania_LV->SetLineWidth(4);
  gr_QPM_Catania_LV->SetLineStyle(1);
  gr_QPM_Catania_LV->Draw("c");

  gr_QPM_Catania_BM->SetLineColor(kBlue);
  gr_QPM_Catania_BM->SetLineWidth(4);
  gr_QPM_Catania_BM->SetLineStyle(1);
  gr_QPM_Catania_BM->Draw("c");


  
  // gr_TAMU_LV->SetLineColor(1);
  // gr_TAMU_LV->SetLineWidth(2);
  // gr_TAMU_LV->Draw("c");

  gr_L_Ding_sys->SetLineWidth(2);
  gr_L_Ding_sys->SetLineColor(1);
  gr_L_Ding_sys->SetFillStyle(0);
  //  gr_L_Ding_sys->Draw("e2");

  gr_L_Ding->SetLineWidth(2);
  gr_L_Ding->SetLineColor(1);
  gr_L_Ding->SetMarkerSize(1.2);
  gr_L_Ding->SetMarkerStyle(24);
  gr_L_Ding->SetMarkerColor(1);
  //  gr_L_Ding->Draw("p");
  
  gr_L_Ding_tot->SetLineWidth(2);
  gr_L_Ding_tot->SetLineColor(1);
  gr_L_Ding_tot->SetMarkerSize(1.2);
  gr_L_Ding_tot->SetMarkerStyle(24);
  gr_L_Ding_tot->SetMarkerColor(1);
  gr_L_Ding_tot->Draw("p");

  gr_L_Banerjee_sys->SetLineWidth(2);
  gr_L_Banerjee_sys->SetLineColor(1);
  gr_L_Banerjee_sys->SetFillStyle(0);
  //  gr_L_Banerjee_sys->Draw("e2");

  gr_L_Banerjee->SetLineWidth(2);
  gr_L_Banerjee->SetLineColor(1);
  gr_L_Banerjee->SetMarkerSize(1.2);
  gr_L_Banerjee->SetMarkerStyle(25);
  gr_L_Banerjee->SetMarkerColor(1);
  //  gr_L_Banerjee->Draw("p");

  gr_L_Banerjee_tot->SetLineWidth(2);
  gr_L_Banerjee_tot->SetLineColor(1);
  gr_L_Banerjee_tot->SetMarkerSize(1.2);
  gr_L_Banerjee_tot->SetMarkerStyle(21);
  gr_L_Banerjee_tot->SetMarkerColor(1);
  gr_L_Banerjee_tot->Draw("p");

  gr_L_Kac->SetLineWidth(2);
  gr_L_Kac->SetLineColor(1);
  gr_L_Kac->SetMarkerSize(1.2);
  gr_L_Kac->SetMarkerStyle(22);
  gr_L_Kac->SetMarkerColor(1);
  gr_L_Kac->Draw("p");
  

  TLatex *tex1[n_txt1];
  for(int i=0;i<n_txt1;i++) {
    if(i>=2&&i<=4) continue;
    tex1[i] = new TLatex(x_txt1[i], y_txt1[i], tex_txt1[i]);
    tex1[i]->SetTextFont(42);
    tex1[i]->SetTextSize(0.03);
    tex1[i]->SetTextAngle(angle_txt1[i]);
    tex1[i]->SetTextColor(kColor[i]);
    tex1[i]->Draw("same");
  }

  TLatex *tex = new TLatex(0.8, 20, "Lattice QCD");
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw("same");
  
  TLegend *leg = new TLegend(0.26, 0.74, 0.4, 0.88);
   leg->SetFillColor(10);
   //   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.03);
   leg->AddEntry(gr_L_Ding_tot,"Ding #it{et al.}","p");
   leg->AddEntry(gr_L_Banerjee_tot,"Banerjee #it{et al.}","p");
   leg->AddEntry(gr_L_Kac,"Kaczmarek #it{et al.}","p");
   leg->Draw();

  /*

  // Experimental data
  TBox *box = new TBox(x2_sep+0.005,y1+0.02,x2-0.005,y2-0.02);
  box->SetFillColor(0);
  //  box->Draw("same");

  TLatex *tex = new TLatex(2.02, y2*0.9, "Exp.");
  tex->SetTextFont(22);
  tex->SetTextSize(0.055);
  tex->Draw("same");
  
  gr_star->SetMarkerStyle(29);
  gr_star->SetMarkerColor(2);
  gr_star->SetMarkerSize(3.0);
  gr_star->SetLineColor(2);
  gr_star->SetLineWidth(2);
  gr_star->Draw("p same");

  TLatex *tex = new TLatex(2.02, y_star[0]+2.0, "STAR");
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw("same");
  */
  
  c1->Update();
  c1->SaveAs("fig/D_HQ_092019.eps");
  c1->SaveAs("fig/D_HQ_092019.pdf");
  c1->SaveAs("fig/D_HQ_092019.png");
}
