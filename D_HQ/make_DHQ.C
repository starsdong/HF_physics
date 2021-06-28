#include <stdio.h>
#include "iomanip.h"

void make_DHQ(const int flag=1)
{
  gROOT->Reset();

  const Double_t twoPi = 3.1415927*2.0;

  const Int_t n_star = 1;
  const Double_t x_star[n_star] = {2.1};
  const Double_t y_star[n_star] = {2.0};
  const Double_t ye_star[n_star] = {1.0};
  const Double_t Tc = 154;

  TGraphErrors *gr_star = new TGraphErrors(n_star, x_star, y_star, 0, ye_star);
  
  const Int_t n_txt1 = 8;
  const Double_t x_txt1[n_txt1] = {0.7, 1.6, 1.6, 1.6, 1.65, 1.65, 1.1, 1.48};
  const Double_t y_txt1[n_txt1] = {16, 32.5, 24, 10., 0.8, 5, 8, 1};
  const Double_t angle_txt1[n_txt1] = {-50, 5, 7, 8, 1, 10, 0, 0};
  const Char_t *tex_txt1[n_txt1] = {"HRG", "pQCD LO", "T-Matrix F-pot.", "T-Matrix U-pot.", "pQCD+HTL", "DpQCD", "Lattice: Banerjee", "Lattice: Ding"};
  
  TGraph *gr_pQCD_LO = new TGraph("/Users/starsdong/work/datapoints/D_HQ/pQCD_LO.txt","%lg %lg");
  TGraph *gr_HRG = new TGraph("/Users/starsdong/work/datapoints/D_HQ/HRG.txt","%lg %lg");
  TGraph *gr_DpQCD = new TGraph("/Users/starsdong/work/datapoints/D_HQ/DpQCD.txt","%lg %lg");
  for(int i=0;i<gr_DpQCD->GetN();i++) {
    gr_DpQCD->GetX()[i] /= Tc;
  }

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

  TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
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
  c1->Draw();

  TPad *p1 = new TPad("p1","",0.0,0.0,0.8,1.0);
  p1->SetFillColor(10);
  p1->SetFillStyle(0);
  p1->SetBorderMode(0);
  p1->SetBorderSize(0);
  p1->SetFrameFillColor(10);
  p1->SetFrameFillStyle(0);
  p1->SetFrameBorderMode(0);
  //p1->SetLogy();
  p1->SetGridx(0);
  p1->SetGridy(0);
  p1->SetTickx(0);
  p1->SetTicky(0);
  p1->SetLeftMargin(0.15);
  p1->SetBottomMargin(0.15);
  p1->SetTopMargin(0.02);
  p1->SetRightMargin(0.001);
  p1->Draw();
  p1->cd();

  double x1 = 0.5;
  double x2 = 1.99;
  double y1 = 0.;
  double y2 = 40.; 
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(205);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("T/T_{c}");
  h0->GetXaxis()->SetTitleOffset(1.);
  h0->GetXaxis()->SetTitleSize(0.07);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.05);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("D #times 2#piT");
  h0->GetYaxis()->SetTitleOffset(1.0);
  h0->GetYaxis()->SetTitleSize(0.07);
  h0->GetYaxis()->SetLabelOffset(0.015);
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

  gr_HRG->SetLineWidth(2);
  gr_HRG->SetLineStyle(4);
  gr_HRG->SetLineColor(4);
  gr_HRG->Draw("c");

  gr_pQCD_LO->SetLineWidth(2);
  gr_pQCD_LO->SetLineStyle(2);
  gr_pQCD_LO->SetLineColor(1);
  gr_pQCD_LO->Draw("c");

  gr_SUB->SetLineColor(16);
  gr_SUB->SetFillColor(16);
  gr_SUB->Draw("e3");

  gr_T_F->SetLineColor(3);
  gr_T_F->SetFillColor(3);
  gr_T_F->Draw("e3");

  gr_T_U->SetLineColor(8);
  gr_T_U->SetFillColor(8);
  gr_T_U->Draw("e3");

  gr_DpQCD->SetLineColor(9);
  gr_DpQCD->SetLineStyle(3);
  gr_DpQCD->SetLineWidth(2);
  gr_DpQCD->Draw("c");

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

  TLatex *tex1[n_txt1];
  for(int i=0;i<n_txt1-2;i++) {  // Lattice labels put into legend
    tex1[i] = new TLatex(x_txt1[i], y_txt1[i], tex_txt1[i]);
    tex1[i]->SetTextFont(42);
    tex1[i]->SetTextSize(0.038);
    tex1[i]->SetTextAngle(angle_txt1[i]);
    tex1[i]->Draw("same");
  }

  if(flag && 0) {
  TLine *l_s1 = new TLine(1, y_star[0]-ye_star[0], x2, y_star[0]-ye_star[0]);
  l_s1->SetLineColor(2);
  l_s1->SetLineWidth(2);
  l_s1->SetLineStyle(2);
  l_s1->Draw("same");
  TLine *l_s2 = new TLine(1, y_star[0]+ye_star[0], x2, y_star[0]+ye_star[0]);
  l_s2->SetLineColor(2);
  l_s2->SetLineWidth(2);
  l_s2->SetLineStyle(2);
  l_s2->Draw("same");
  }
  
  TLegend *leg = new TLegend(0.18, 0.82, 0.4, 0.94);
  leg->SetFillColor(10);
  leg->SetLineStyle(4000);
  leg->SetLineColor(10);
  leg->SetLineWidth(0.);
  leg->SetTextSize(0.035);
  leg->AddEntry(gr_L_Banerjee_tot, "Lattice QCD: Banerjee et al.", "p");
  leg->AddEntry(gr_L_Ding_tot, "Lattice QCD: Ding et al.", "p");
  leg->Draw();
  
  p1->Modified();
  c1->Update();
  c1->cd();
  
  TPad *p2 = new TPad("p2","",0.8,0.0,1.0,1.0);
  p2->SetFillColor(10);
  p2->SetFillStyle(0);
  p2->SetBorderMode(0);
  p2->SetBorderSize(0);
  p2->SetFrameFillColor(10);
  p2->SetFrameFillStyle(0);
  p2->SetFrameBorderMode(0);
  //p2->SetLogy();
  p2->SetGridx(0);
  p2->SetGridy(0);
  p2->SetTickx(0);
  p2->SetTicky(0);
  p2->SetLeftMargin(0.01);
  p2->SetBottomMargin(0.15);
  p2->SetTopMargin(0.02);
  p2->SetRightMargin(0.4);
  p2->Draw();
  p2->cd();

  gStyle->SetFrameLineStyle(2);
  p2->SetTicks(1,2);
  
  double x1 = 2.0;
  double x2 = 2.19;
  double y1 = 0.;
  double y2 = 40.; 
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(101);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("");
  h0->GetXaxis()->SetTitleOffset(999);
  h0->GetXaxis()->SetTitleSize(0.0001);
  h0->GetXaxis()->SetLabelOffset(999);
  h0->GetXaxis()->SetLabelSize(0.0001);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTitle("");
  h0->GetYaxis()->SetTitleOffset(1.0);
  h0->GetYaxis()->SetTitleSize(0.07);
  h0->GetYaxis()->SetLabelOffset(0.03);
  h0->GetYaxis()->SetLabelSize(0.18);
  h0->GetYaxis()->SetLabelFont(42);
  h0->GetYaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetTickLength(0.1);
  h0->Draw("c");

  TBox *box = new TBox(x1-0.05,y1-0.05,x2+0.05,y2+0.05);
  box->SetFillColor(0);
  //  box->Draw("same");
  
  TLine *l1 = new TLine(x1,y1,x2,y1);
  l1->SetLineWidth(3);
  //  l1->SetLineStyle(9);
  l1->Draw("same");
  TLine *l2 = new TLine(x1,y2,x2,y2);
  l2->SetLineWidth(3);
  //  l2->SetLineStyle(9);
  l2->Draw("same");
  TLine *l3 = new TLine(x1,y1,x1,y2);
  l3->SetLineWidth(3);
  //  l3->SetLineStyle(9);
  l3->Draw("same");
  TLine *l4 = new TLine(x2,y1,x2,y2);
  l4->SetLineWidth(3);
  //  l4->SetLineStyle(9);
  l4->Draw("same");
  
  // Experimental data
  TLatex *tex = new TLatex(2.07, y2*0.95, "Exp./Th.");
  tex->SetTextFont(22);
  tex->SetTextSize(0.25);
  tex->SetTextAngle(-90);
  tex->Draw("same");

  if(flag) {
  gr_star->SetMarkerStyle(29);
  gr_star->SetMarkerColor(2);
  gr_star->SetMarkerSize(3.0);
  gr_star->SetLineColor(2);
  gr_star->SetLineWidth(2);
  gr_star->Draw("p same");

  TLatex *tex = new TLatex(2.03, y_star[0]+2.0, "STAR");
  tex->SetTextFont(42);
  tex->SetTextSize(0.2);
  tex->Draw("same");

  TLine *l_s1 = new TLine(2, y_star[0]-ye_star[0], x2, y_star[0]-ye_star[0]);
  l_s1->SetLineColor(2);
  l_s1->SetLineWidth(2);
  l_s1->SetLineStyle(2);
  l_s1->Draw("same");
  TLine *l_s2 = new TLine(2, y_star[0]+ye_star[0], x2, y_star[0]+ye_star[0]);
  l_s2->SetLineColor(2);
  l_s2->SetLineWidth(2);
  l_s2->SetLineStyle(2);
  l_s2->Draw("same");
  }
  
  
  c1->Update();
  c1->SaveAs(Form("fig/D_HQ_%d.eps",flag));
  c1->SaveAs(Form("fig/D_HQ_%d.pdf",flag));
  c1->SaveAs(Form("fig/D_HQ_%d.png",flag));
}
