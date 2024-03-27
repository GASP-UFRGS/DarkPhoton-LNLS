void photonTotalEnergy()
{
    TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);

    TFile *input = new TFile("output.root", "read");

    TTree *tree = (TTree*)input->Get("PhotonHits");

    int EventID; 
    double PhotonEnergy, photonX, photonY;

    tree->SetBranchAddress("PhotonEnergy", &PhotonEnergy);
    tree->SetBranchAddress("EventID", &EventID);

    int entries = tree->GetEntries();

    //cout << entries << endl;

    TH1F *hist = new TH1F("hist", "PhotonEnergy", 200, 0, 600); //name, title, n_bins, range1, range2

    for(int i = 0; i < entries; i++) {
        tree->GetEntry(i);

	cout << PhotonEnergy << " " << EventID << endl;

	hist->Fill(PhotonEnergy);
    }

    hist->Draw();

    c2->SaveAs("photonHisto.png");

    input->Close();
}

