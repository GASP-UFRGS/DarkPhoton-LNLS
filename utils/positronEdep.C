void positronEdep() 
{
    TCanvas *c3 = new TCanvas();

    TFile *input = new TFile("output.root", "read");
	
    TTree *tree = (TTree*)input->Get("EventAction");
	
    int PositronEventID;
    double caloEdep, posEdep, caloTrackLength, posTrackLength;

    tree->SetBranchAddress("posEdep", &posEdep);
	
    int entries = tree->GetEntries();
	
    TH1F *hist = new TH1F("hist", "posEdep", 200, 0, 2); //name, title, n_bins, range1, range2
    
    for(int i = 0; i < entries; i++) {
	tree->GetEntry(i);
				
	hist->Fill(posEdep);
    }
	
    hist->Draw();

    c3->SaveAs("positronEdep.png");

    input->Close();
}

