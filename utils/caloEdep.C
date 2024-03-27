void caloEdep() 
{
    TCanvas *c4 = new TCanvas();

    TFile *input = new TFile("output.root", "read");
	
    TTree *tree = (TTree*)input->Get("EventAction");
	
    int PositronEventID;
    double caloEdep, posEdep, caloTrackLength, posTrackLength;

    tree->SetBranchAddress("caloEdep", &caloEdep);

    int entries = tree->GetEntries();
	
    TH1F *hist = new TH1F("hist", "caloEdep", 200, 0, 0.01); //name, title, n_bins, range1, range2

    for(int i = 0; i < entries; i++) {
        tree->GetEntry(i);
		
	hist->Fill(caloEdep);
    }
	
    hist->Draw();

    c4->SaveAs("caloEdep.png");

    input->Close();
}

