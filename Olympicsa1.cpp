#include "Olympicsa1.h"



Olympics::Olympics() : m_TeamTree(new AVLTree<int, Team>()), m_countryTree(new AVLTree<int, Country>()) ,
m_contestantTree(new AVLTree<int, Contestant>()){}

Olympics::~Olympics(){
    delete m_TeamTree;
    delete m_countryTree;
    delete m_contestantTree;
}
//all done except from try catch
StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_countryTree->findKey(countryId, m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* newCountry = new Country(countryId,medals);
    if(newCountry == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Country>* node = new Node<int,Country>(countryId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    node->setData(newCountry);
    m_countryTree->insertNodeToTree(node,m_countryTree->getRoot());
    return StatusType::SUCCESS;
}
//try catch???
StatusType Olympics::remove_country(int countryId){
    if(countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_countryTree->findKey(countryId, m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if((m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->get_numsContestant() != 0)
       || (m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->get_numsTeam() != 0)){
        return StatusType::FAILURE;
    }
    delete m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData();
    m_countryTree->findKey(countryId,m_countryTree->getRoot())->setData(nullptr);
    m_countryTree->DeleteNodeFromTree(m_countryTree->getRoot(),countryId);

    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    if (teamId <=0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    if(m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* curr = m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData();
    Team* newTeam = new Team(teamId,curr,sport);
    if(newTeam == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Team>* node = new Node<int,Team>(teamId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->addOneTeam();
    node->setData(newTeam);
    m_TeamTree->insertNodeToTree(node,m_TeamTree->getRoot());
    return StatusType::SUCCESS;
}


StatusType Olympics::remove_team(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getNumOfContestant() > 0){
        return StatusType::FAILURE;
    }
    delete m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData();
    m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->setData(nullptr);
    m_TeamTree->DeleteNodeFromTree(m_TeamTree->getRoot(),teamId);
    return StatusType::SUCCESS;
}
//try catchhhhhhh
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if (countryId <= 0 || contestantId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    if(m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* currCountry = m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData();
    Contestant* newContestant = new Contestant(contestantId, currCountry, sport,strength);
    if(newContestant == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Contestant>* node = new Node<int,Contestant>(contestantId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    node->setData(newContestant);
    m_contestantTree->insertNodeToTree(node,m_contestantTree->getRoot());
    currCountry->addOneContestant();
    return StatusType::SUCCESS;
}
//try catch
StatusType Olympics::remove_contestant(int contestantId){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_contestantTree->findKey(contestantId, m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData()->get_numTeam() > 0){
        return StatusType::FAILURE;
    }
    delete (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData());
    m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->setData(nullptr);
    m_contestantTree->DeleteNodeFromTree(m_contestantTree->getRoot(),contestantId);
    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if (contestantId <= 0 || teamId <= 0 ){
        return StatusType::INVALID_INPUT;
    }
    Node<int,Team>* teamNode =  m_TeamTree->findKey(teamId, m_TeamTree->getRoot());
    Node<int,Contestant>* contestantNode = m_contestantTree->findKey(contestantId, m_contestantTree->getRoot());
    if (teamNode == nullptr || contestantNode == nullptr ){
        return StatusType::FAILURE;
    }
    if (teamNode->getData()->getSport() != contestantNode->getData()->get_sport()){
        return StatusType::FAILURE;
    }
    if (teamNode->getData()->getCountry()->get_countryID() != contestantNode->getData()->get_Country()->get_countryID()){
        return StatusType::FAILURE;
    }
    if (contestantNode->getData()->get_numTeam() == THREE ){
        return StatusType::FAILURE;
    }
    for (int i = 0; i < THREE ; ++i) {
        if (contestantNode->getData()->get_teamsArr()[i] == teamId ){
            return StatusType::FAILURE;
        }
    }
    Node<int,Contestant>* contestantNodeToInsert =  new Node<int,Contestant>(contestantId,contestantNode->getData());

    StrengthPairKey key = StrengthPairKey(contestantNode->getData()->get_strength() ,contestantId);
    Node<StrengthPairKey,StrengthInfo>* StrengthNodeToInsert =  new Node<StrengthPairKey,StrengthInfo>(key);
    teamNode->getData()->addContestantToChosenTeam(contestantNodeToInsert,StrengthNodeToInsert );
    contestantNodeToInsert->getData()->increaseTeamNumAndArray(teamId);
    teamNode->getData()->increaseNumOfContestants();
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    if (contestantId <= 0 || teamId <= 0 ){
        return StatusType::INVALID_INPUT;
    }
    Node<int,Team>* teamNode =  m_TeamTree->findKey(teamId, m_TeamTree->getRoot());
    Node<int,Contestant>* contestantNode = m_contestantTree->findKey(contestantId, m_contestantTree->getRoot());
    if (teamNode == nullptr || contestantNode == nullptr ){
        return StatusType::FAILURE;
    }
    if (teamNode->getData()->getSport() != contestantNode->getData()->get_sport()){
        return StatusType::FAILURE;
    }
    if (teamNode->getData()->getCountry()->get_countryID() != contestantNode->getData()->get_Country()->get_countryID()){
        return StatusType::FAILURE;
    }
    if (contestantNode->getData()->get_numTeam() == 0 ){
        return StatusType::FAILURE;
    }
    for (int i = 0; i < THREE ; ++i) {
        if (contestantNode->getData()->get_teamsArr()[i] == teamId) {
            int contestantStrength = contestantNode->getData()->get_strength();
            //removes and updated the team strength and even trees
            teamNode->getData()->removeContestantFromChosenTeam(contestantId, contestantStrength);
            //update the fields
            contestantNode->getData()->decreaseTeamNumAndArray(teamId);
            teamNode->getData()->decreaseNumOfContestants();
        }
    }
    return StatusType::FAILURE;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Node<int,Contestant>* currContestant = m_contestantTree->findKey(contestantId, m_contestantTree->getRoot());
    int oldStrength = currContestant->getData()->get_strength();
    int newStrength = oldStrength + change;
    if (newStrength < 0){
        return StatusType::FAILURE;
    }
    currContestant->getData()->set_strength(newStrength);
    for (int i = 0; i < currContestant->getData()->get_numTeam() ; ++i) {
        Node<int, Team> *teamNode = m_TeamTree->findKey(currContestant->getData()->get_teamsArr()[i],
                                                        m_TeamTree->getRoot());

        StrengthPairKey oldKey = StrengthPairKey(oldStrength, currContestant->getKey());
        StrengthPairKey newKey = StrengthPairKey(newStrength, currContestant->getKey());

        Node<StrengthPairKey, StrengthInfo> *currRootLeft = teamNode->getData()->getRightTreeStrength()->getRoot();
        Node<StrengthPairKey, StrengthInfo> *currRootRight = teamNode->getData()->getRightTreeStrength()->getRoot();
        Node<StrengthPairKey, StrengthInfo> *currRootMiddle = teamNode->getData()->getMiddleTreeStrength()->getRoot();

        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeLeft = teamNode->getData()->getLeftTreeStrength()->findKey(
                oldKey,
                teamNode->getData()->getLeftTreeStrength()->getRoot());
        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeRight = teamNode->getData()->getRightTreeStrength()->findKey(
                oldKey,
                teamNode->getData()->getLeftTreeStrength()->getRoot());
        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeMiddle = teamNode->getData()->getMiddleTreeStrength()->findKey(
                oldKey,
                teamNode->getData()->getLeftTreeStrength()->getRoot());

        Node<StrengthPairKey, StrengthInfo> *newStrengthNode = new Node<StrengthPairKey, StrengthInfo>(newKey,
                                                                                                       currContestant->getData()->getStrengthInfo());
        //looking for the strength in left tree
        if (oldStrengthNodeLeft != nullptr) {
            teamNode->getData()->getLeftTreeStrength()->DeleteNodeFromTree(currRootLeft, oldKey);
            teamNode->getData()->getLeftTreeStrength()->insertNodeToTree(newStrengthNode, currRootLeft);
        }
            //looking for the strength in right tree
        else if (oldStrengthNodeRight != nullptr) {
            teamNode->getData()->getRightTreeStrength()->DeleteNodeFromTree(currRootRight, oldKey);
            teamNode->getData()->getRightTreeStrength()->insertNodeToTree(newStrengthNode, currRootRight);
        }
            //looking for the strength in middle tree
        else if (oldStrengthNodeMiddle != nullptr) {
            teamNode->getData()->getMiddleTreeStrength()->DeleteNodeFromTree(currRootMiddle, oldKey);
            teamNode->getData()->getMiddleTreeStrength()->insertNodeToTree(newStrengthNode, currRootMiddle);
        }
        //update team strength
        teamNode->getData()->setTeamStrength(teamNode->getData()->calcStrength());
    }

    return StatusType::SUCCESS;
}

output_t<int> Olympics::get_strength(int contestantId){
    if (contestantId <= 0){
        return StatusType::FAILURE;
    }
    if (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData()->get_strength();
}

output_t<int> Olympics::get_medals(int countryId){
    if (countryId <= 0){
        return StatusType::FAILURE;
    }
    if (m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->get_medals();

}

output_t<int> Olympics::get_team_strength(int teamId){
    if (teamId <= 0 || m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getTeamStrength();
}

StatusType Olympics::unite_teams(int teamId1,int teamId2) {
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    
    if (m_TeamTree->findKey(teamId1, m_TeamTree->getRoot()) == nullptr ||
        m_TeamTree->findKey(teamId2, m_TeamTree->getRoot()) == nullptr) {
        return StatusType::FAILURE;
    }
    Team* team1 = m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData();
    Team* team2 = m_TeamTree->findKey(teamId2, m_TeamTree->getRoot())->getData();
    if (team1->getSport() != team2->getSport()) {
        return StatusType::FAILURE;
    }
    if (team1->getCountry()->get_countryID() != team2->getCountry()->get_countryID()) {
        return StatusType::FAILURE;
    }
    //creating array and fills them with pointers according to the placement in the avl tree
    Contestant** contestantArray1 = new Contestant * [team1->getNumOfContestant()];
    Contestant** contestantArray2 = new Contestant * [team2->getNumOfContestant()];


    int index1 = 0;
    team1->getLeftTreeID()->convertTreeToArray(team1->getLeftTreeID()->getRoot(),contestantArray1, &index1);
    team1->getMiddleTreeID()->convertTreeToArray(team1->getMiddleTreeID()->getRoot(),contestantArray1, &index1);
    team1->getRightTreeID()->convertTreeToArray(team1->getRightTreeID()->getRoot(),contestantArray1, &index1);

    int index2 = 0;
    team2->getLeftTreeID()->convertTreeToArray(team2->getLeftTreeID()->getRoot(),contestantArray2, &index2);
    team2->getMiddleTreeID()->convertTreeToArray(team2->getMiddleTreeID()->getRoot(),contestantArray2, &index2);
    team2->getRightTreeID()->convertTreeToArray(team2->getRightTreeID()->getRoot(),contestantArray2, &index2);

    StrengthInfo** strengthArray1 = new StrengthInfo * [team1->getNumOfContestant()];
    StrengthInfo** strengthArray2 = new StrengthInfo * [team2->getNumOfContestant()];


    StrengthInfo** strengthArrayLeft1 = new StrengthInfo * [team1->getLeftTreeStrength()->getNodeCount()];
    StrengthInfo** strengthArrayLeft2 = new StrengthInfo * [team2->getLeftTreeStrength()->getNodeCount()];
    StrengthInfo** strengthArrayMiddle1 = new StrengthInfo * [team1->getMiddleTreeStrength()->getNodeCount()];
    StrengthInfo** strengthArrayMiddle2 = new StrengthInfo * [team2->getMiddleTreeStrength()->getNodeCount()];
    StrengthInfo** strengthArrayRight1 = new StrengthInfo * [team1->getRightTreeStrength()->getNodeCount()];
    StrengthInfo** strengthArrayRight2 = new StrengthInfo * [team2->getRightTreeStrength()->getNodeCount()];

    StrengthInfo** strengthArrayLeftMiddle1 = new StrengthInfo *


    StrengthInfo** strengthArrayLeftMiddle1 = new StrengthInfo * [team1->getLeftTreeStrength()->getNodeCount()+team1->getMiddleTreeStrength()->getNodeCount()];
            [team1->getLeftTreeStrength()->getNodeCount()+team1->getMiddleTreeStrength()->getNodeCount()];

    merge(strengthArrayLeft1,team1->getLeftTreeStrength()->getNodeCount(), strengthArrayMiddle1,team1->getMiddleTreeStrength(),strengthArrayLeftMiddle1);









    Contestant** contestantArrayUniteRep = new Contestant * [team1->getNumOfContestant()+team2->getNumOfContestant()];
    merge(contestantArray1,team1->getNumOfContestant(),contestantArray2,team2->getNumOfContestant(),contestantArrayUniteRep  );

    StrengthInfo** strengthArrayUniteRep = new StrengthInfo * [team1->getNumOfContestant()+team2->getNumOfContestant()];
    merge(strengthArray1,team1->getNumOfContestant(),strengthArray2,team2->getNumOfContestant(),strengthArrayUniteRep  );

    delete[] contestantArray1;
    delete[] contestantArray2;

    delete[] strengthArray1;
    delete[] strengthArray2;

    int countRep= 0;
    for (int i = 0; i <team1->getNumOfContestant()+team2->getNumOfContestant()-1  ; ++i) {
        if (contestantArrayUniteRep[i]->get_contestantID() == contestantArrayUniteRep[i + 1]->get_contestantID()) {
            contestantArrayUniteRep[i] = nullptr;
            i++;
            countRep++;
        }
    }
    int newNumOfContestants = team1->getNumOfContestant()+team2->getNumOfContestant() - countRep;
    Contestant** contestantArrayUniteNoRep = new Contestant * [newNumOfContestants];
    for (int j=0, i = 0 ; i <team1->getNumOfContestant()+team2->getNumOfContestant() ; ++i) {
        if (contestantArrayUniteRep[i]!= nullptr) {
            contestantArrayUniteNoRep[j] = contestantArrayUniteRep[i];
            j++;
        }
    }
////////////////////////////////////////
    for (int i = 0; i <team1->getNumOfContestant()+team2->getNumOfContestant()-1  ; ++i) {
        if (contestantArrayUniteRep[i]->get_contestantID() == contestantArrayUniteRep[i + 1]->get_contestantID()) {
            contestantArrayUniteRep[i] = nullptr;
            i++;
            countRep++;
        }
    }
    int newNumOfContestants = team1->getNumOfContestant()+team2->getNumOfContestant() - countRep;
    Contestant** contestantArrayUniteNoRep = new Contestant * [newNumOfContestants];
    for (int j=0, i = 0 ; i <team1->getNumOfContestant()+team2->getNumOfContestant() ; ++i) {
        if (contestantArrayUniteRep[i]!= nullptr) {
            contestantArrayUniteNoRep[j] = contestantArrayUniteRep[i];
            j++;
        }
    }
    /////////////////////////////////////////////////



    delete[] contestantArrayUniteRep;
    team1->setNumOfContestant(newNumOfContestants);

    delete team1->getLeftTreeID();
    team1->setLeftTreeID(nullptr);

    delete team1->getMiddleTreeID();
    team1->setMiddleTreeID(nullptr);

    delete team1->getRightTreeID();
    team1->setRightTreeID(nullptr);

    int newNumOfContestantsLeft =0,  newNumOfContestantsMiddle = 0, newNumOfContestantsRight = 0 ;;

    if (newNumOfContestants%THREE == 0 ) {
        newNumOfContestantsLeft = newNumOfContestants/THREE;
        newNumOfContestantsMiddle=newNumOfContestants/THREE;
        newNumOfContestantsRight=newNumOfContestants/THREE;
    }
    else if (newNumOfContestants%THREE == 1 ) {
        newNumOfContestantsLeft = newNumOfContestants/THREE+1;
        newNumOfContestantsMiddle=newNumOfContestants/THREE;
        newNumOfContestantsRight=newNumOfContestants/THREE;
    }
    else if (newNumOfContestants%THREE == 2 ) {
        newNumOfContestantsLeft = newNumOfContestants/THREE+1;
        newNumOfContestantsMiddle=newNumOfContestants/THREE+1;
        newNumOfContestantsRight=newNumOfContestants/THREE;
    }
    AVLTree<int, Contestant>* newLeftTreeID = new AVLTree<int, Contestant>();
    newLeftTreeID->buildTreeBeforeInsertArray(newNumOfContestantsLeft);
    team1->setLeftTreeID(newLeftTreeID);

    AVLTree<int, Contestant>* newMiddleTreeID = new AVLTree<int, Contestant>();
    newMiddleTreeID->buildTreeBeforeInsertArray(newNumOfContestantsMiddle);
    team1->setMiddleTreeID(newMiddleTreeID);

    AVLTree<int, Contestant>* newRightTreeID = new AVLTree<int, Contestant>();
    newRightTreeID->buildTreeBeforeInsertArray(newNumOfContestantsRight);
    team1->setRightTreeID(newRightTreeID);

    int indexID=0;
    team1->getLeftTreeID()->convertArrayToTree(team1->getLeftTreeID()->getRoot(),contestantArrayUniteNoRep, &indexID);
    team1->getMiddleTreeID()->convertArrayToTree(team1->getMiddleTreeID()->getRoot(),contestantArrayUniteNoRep, &indexID);
    team1->getRightTreeID()->convertArrayToTree(team1->getRightTreeID()->getRoot(),contestantArrayUniteNoRep, &indexID);

    delete[] contestantArrayUniteNoRep;






////////////////////////////////////////
            return remove_team(teamId2);
    }

}


StatusType Olympics::play_match(int teamId1,int teamId2){
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    if (m_TeamTree->findKey(teamId1, m_TeamTree->getRoot()) == nullptr ||
    m_TeamTree->findKey(teamId2, m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if(m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData()->getSport() !=
    m_TeamTree->findKey(teamId2, m_TeamTree->getRoot())->getData()->getSport()){
        return StatusType::FAILURE;
    }
    int medalT1 = m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData()->getCountry()->get_medals();
    int medalT2 = m_TeamTree->findKey(teamId2, m_TeamTree->getRoot())->getData()->getCountry()->get_medals();
    int pointTeam1 = medalT1 + get_team_strength(teamId1).ans();
    int pointTeam2 = medalT2 + get_team_strength(teamId1).ans();
    if(pointTeam1 > pointTeam2){
        m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData()->getCountry()->countryWonMedal();
    }
    else if (pointTeam1 > pointTeam2){
        m_TeamTree->findKey(teamId2, m_TeamTree->getRoot())->getData()->getCountry()->countryWonMedal();
    }
    return StatusType::SUCCESS;
}

output_t<int> Olympics::austerity_measures(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr ||
    m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getNumOfContestant() < 3){
        return StatusType::FAILURE;
    }
    return 0;
}

