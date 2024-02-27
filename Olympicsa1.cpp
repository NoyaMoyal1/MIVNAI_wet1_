#include "Olympicsa1.h"



Olympics::Olympics() :  m_countryTree(new AVLTree<int, Country>()) ,m_TeamTree(new AVLTree<int, Team>()),
                        m_contestantTree(new AVLTree<int, Contestant>()){}

Olympics::~Olympics(){

    m_TeamTree->deleteAllTreeData(m_TeamTree->getRoot());
    m_countryTree->deleteAllTreeData(m_countryTree->getRoot());
    m_contestantTree->deleteAllTreeData(m_contestantTree->getRoot());

    delete m_countryTree;
    delete m_TeamTree;
    delete m_contestantTree;
}
//all done except from try catch
StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals < 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_countryTree->getRoot() != nullptr && m_countryTree->findKey(countryId, m_countryTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    Country* newCountry;
    try{
        newCountry = new Country(countryId,medals);
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Country>* node;
    try{
        node = new Node<int,Country>(countryId);
    }
    catch (const std::bad_alloc &e)
    {
        delete newCountry;
        return StatusType::ALLOCATION_ERROR;
    }

    node->setData(newCountry);
    m_countryTree->setRoot(m_countryTree->insertNodeToTree(node,m_countryTree->getRoot()));
    return StatusType::SUCCESS;
}

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
    m_countryTree->setRoot(m_countryTree->DeleteNodeFromTree(m_countryTree->getRoot(),countryId));

    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    if (teamId <=0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->getRoot() != nullptr && m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    if(m_countryTree->getRoot() == nullptr || m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* curr = m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData();
    Team* newTeam;
    try{
        newTeam = new Team(teamId,curr,sport);
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Team>* node;
    try{
        node = new Node<int,Team>(teamId);
    }
    catch (const std::bad_alloc &e)
    {
        delete newTeam;
        return StatusType::ALLOCATION_ERROR;
    }

    m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->addOneTeam();
    node->setData(newTeam);
    m_TeamTree->setRoot(m_TeamTree->insertNodeToTree(node,m_TeamTree->getRoot()));
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
    m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getCountry()->removeOneTeam();
    delete m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData();
    m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->setData(nullptr);
    m_TeamTree->setRoot(m_TeamTree->DeleteNodeFromTree(m_TeamTree->getRoot(),teamId));

    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if (countryId <= 0 || contestantId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_contestantTree->getRoot() != nullptr && m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    if(m_countryTree == nullptr || m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* currCountry = m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData();
    Contestant* newContestant;
    try{
        newContestant = new Contestant(contestantId, currCountry, sport,strength);
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Contestant>* node;
    try{
        node = new Node<int,Contestant>(contestantId);
    }
    catch (const std::bad_alloc &e)
    {
        delete newContestant;
        return StatusType::ALLOCATION_ERROR;
    }

    node->setData(newContestant);
    m_contestantTree->setRoot(m_contestantTree->insertNodeToTree(node,m_contestantTree->getRoot()));
    currCountry->addOneContestant();
    return StatusType::SUCCESS;
}

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
    m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData()->get_Country()->removeOneContestant();
    delete (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData());
    m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->setData(nullptr);
    m_contestantTree->setRoot(m_contestantTree->DeleteNodeFromTree(m_contestantTree->getRoot(),contestantId));
    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if (contestantId <= 0 || teamId <= 0 ){
        return StatusType::INVALID_INPUT;
    }
    if (m_TeamTree->getRoot() == nullptr ||  m_contestantTree->getRoot() == nullptr){
        return StatusType::FAILURE;
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
    Node<int,Contestant>* contestantNodeToInsert;
    try{
        contestantNodeToInsert =  new Node<int,Contestant>(contestantId,contestantNode->getData());
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    StrengthPairKey key = StrengthPairKey(contestantNode->getData()->get_strength() ,contestantId);
    Node<StrengthPairKey,StrengthInfo>* StrengthNodeToInsert;
    try{
        StrengthNodeToInsert = new Node<StrengthPairKey,StrengthInfo>(key,contestantNodeToInsert->getData()->getStrengthInfo());
    }
    catch (const std::bad_alloc &e)
    {
        delete contestantNode;
        return StatusType::ALLOCATION_ERROR;
    }

    contestantNodeToInsert->getData()->increaseTeamNumAndArray(teamId);
    teamNode->getData()->increaseNumOfContestants();

    teamNode->getData()->addContestantToChosenTeam(contestantNodeToInsert,StrengthNodeToInsert );
    //even tree moves the node thefore this parameter isnt valid anymore
    contestantNodeToInsert = nullptr;

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
    bool flag = false;
    for (int i = 0; i < THREE ; ++i) {
        if (contestantNode->getData()->get_teamsArr()[i] == teamId) {
            flag = true;
            int contestantStrength = contestantNode->getData()->get_strength();
            //removes and updated the team strength and even trees
            teamNode->getData()->decreaseNumOfContestants();
            teamNode->getData()->removeContestantFromChosenTeam(contestantId, contestantStrength);
            //update the fields
            contestantNode->getData()->decreaseTeamNumAndArray(teamId);
            break;
        }
    }
    if (flag) return StatusType::SUCCESS;
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
        Node<int, Team> *teamNode = m_TeamTree->findKey(currContestant->getData()->get_teamsArr()[i],m_TeamTree->getRoot());

        StrengthPairKey oldKey = StrengthPairKey(oldStrength, currContestant->getKey());
        StrengthPairKey newKey = StrengthPairKey(newStrength, currContestant->getKey());

        Node<StrengthPairKey, StrengthInfo> *currRootLeft = teamNode->getData()->getLeftTreeStrength()->getRoot();
        Node<StrengthPairKey, StrengthInfo> *currRootRight = teamNode->getData()->getRightTreeStrength()->getRoot();
        Node<StrengthPairKey, StrengthInfo> *currRootMiddle = teamNode->getData()->getMiddleTreeStrength()->getRoot();

        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeLeft = teamNode->getData()->getLeftTreeStrength()->findKey(oldKey,currRootLeft);
        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeRight = teamNode->getData()->getRightTreeStrength()->findKey(oldKey,currRootRight);
        Node<StrengthPairKey, StrengthInfo> *oldStrengthNodeMiddle = teamNode->getData()->getMiddleTreeStrength()->findKey(oldKey,currRootMiddle);

        Node<StrengthPairKey, StrengthInfo> *newStrengthNode;
        try{
            newStrengthNode = new Node<StrengthPairKey, StrengthInfo>(newKey, currContestant->getData()->getStrengthInfo());
        }
        catch (const std::bad_alloc &e)
        {
            return StatusType::ALLOCATION_ERROR;
        }

        //looking for the strength in left tree
        if (oldStrengthNodeLeft != nullptr) {
            teamNode->getData()->getLeftTreeStrength()->setRoot(teamNode->getData()->getLeftTreeStrength()->DeleteNodeFromTree(currRootLeft, oldKey));
            currRootLeft = teamNode->getData()->getLeftTreeStrength()->getRoot();
            teamNode->getData()->getLeftTreeStrength()->setRoot(teamNode->getData()->getLeftTreeStrength()->insertNodeToTree(newStrengthNode, currRootLeft));
        }
            //looking for the strength in right tree
        else if (oldStrengthNodeRight != nullptr) {
            teamNode->getData()->getRightTreeStrength()->setRoot(teamNode->getData()->getRightTreeStrength()->DeleteNodeFromTree(currRootRight, oldKey));
            currRootRight = teamNode->getData()->getRightTreeStrength()->getRoot();
            teamNode->getData()->getRightTreeStrength()->setRoot(teamNode->getData()->getRightTreeStrength()->insertNodeToTree(newStrengthNode, currRootRight));
        }
            //looking for the strength in middle tree
        else if (oldStrengthNodeMiddle != nullptr) {
            teamNode->getData()->getMiddleTreeStrength()->setRoot(teamNode->getData()->getMiddleTreeStrength()->DeleteNodeFromTree(currRootMiddle, oldKey));
            currRootMiddle = teamNode->getData()->getMiddleTreeStrength()->getRoot();
            teamNode->getData()->getMiddleTreeStrength()->setRoot(teamNode->getData()->getMiddleTreeStrength()->insertNodeToTree(newStrengthNode, currRootMiddle));
        }
        //update team strength
        teamNode->getData()->setTeamStrength(teamNode->getData()->calcStrength());
        try{
            teamNode->getData()->calcAusterity();
        }
        catch (const std::bad_alloc &e)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    return StatusType::SUCCESS;
}

output_t<int> Olympics::get_strength(int contestantId){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_contestantTree->findKey(contestantId,m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData()->get_strength();
}

output_t<int> Olympics::get_medals(int countryId){
    if (countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->get_medals();

}

output_t<int> Olympics::get_team_strength(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;

    }
    if (m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return (m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getTeamStrength());
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
    Contestant** contestantArray1;
    Contestant** contestantArray2;
    try{
        contestantArray1 = new Contestant * [team1->getNumOfContestant()];
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        contestantArray2 = new Contestant * [team2->getNumOfContestant()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }

    int index1 = 0;
    team1->getLeftTreeID()->convertTreeToArray(team1->getLeftTreeID()->getRoot(),contestantArray1, &index1);
    team1->getMiddleTreeID()->convertTreeToArray(team1->getMiddleTreeID()->getRoot(),contestantArray1, &index1);
    team1->getRightTreeID()->convertTreeToArray(team1->getRightTreeID()->getRoot(),contestantArray1, &index1);

    int index2 = 0;
    team2->getLeftTreeID()->convertTreeToArray(team2->getLeftTreeID()->getRoot(),contestantArray2, &index2);
    team2->getMiddleTreeID()->convertTreeToArray(team2->getMiddleTreeID()->getRoot(),contestantArray2, &index2);
    team2->getRightTreeID()->convertTreeToArray(team2->getRightTreeID()->getRoot(),contestantArray2, &index2);

    StrengthInfo** strengthArrayLeft1;
    StrengthInfo** strengthArrayLeft2;
    StrengthInfo** strengthArrayMiddle1;
    StrengthInfo** strengthArrayMiddle2;
    StrengthInfo** strengthArrayRight1;
    StrengthInfo** strengthArrayRight2;

    try{
        strengthArrayLeft1 = new StrengthInfo * [team1->getLeftTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArrayLeft2 = new StrengthInfo * [team2->getLeftTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArrayMiddle1 = new StrengthInfo * [team1->getMiddleTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArrayMiddle2 = new StrengthInfo * [team2->getMiddleTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArrayRight1 = new StrengthInfo * [team1->getRightTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArrayRight2 = new StrengthInfo * [team2->getRightTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayRight1;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }

    int index=0;
    team1->getLeftTreeStrength()->convertTreeToArray(team1->getLeftTreeStrength()->getRoot(), strengthArrayLeft1,&index);
    index = 0;
    team1->getMiddleTreeStrength()->convertTreeToArray(team1->getMiddleTreeStrength()->getRoot(), strengthArrayMiddle1,&index);
    index = 0;
    team1->getRightTreeStrength()->convertTreeToArray(team1->getRightTreeStrength()->getRoot(), strengthArrayRight1,&index);
    index = 0;
    team2->getLeftTreeStrength()->convertTreeToArray(team2->getLeftTreeStrength()->getRoot(), strengthArrayLeft2,&index);
    index = 0;
    team2->getMiddleTreeStrength()->convertTreeToArray(team2->getMiddleTreeStrength()->getRoot(), strengthArrayMiddle2,&index);
    index = 0;
    team2->getRightTreeStrength()->convertTreeToArray(team2->getRightTreeStrength()->getRoot(), strengthArrayRight2,&index);
    index = 0;

    StrengthInfo** strengthArrayLeftMiddle1;
    StrengthInfo** strengthArray1;
    StrengthInfo** strengthArrayLeftMiddle2;
    StrengthInfo** strengthArray2;
    StrengthInfo** strengthArrayUniteRep;
    try{
        strengthArrayLeftMiddle1 = new StrengthInfo * [team1->getLeftTreeStrength()->getNodeCount()+team1->getMiddleTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayRight2;
        delete[] strengthArrayRight1;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArray1 = new StrengthInfo * [team1->getNumOfContestant()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayLeftMiddle1;
        delete[] strengthArrayRight2;
        delete[] strengthArrayRight1;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArrayLeftMiddle2 = new StrengthInfo * [team2->getLeftTreeStrength()->getNodeCount()+team2->getMiddleTreeStrength()->getNodeCount()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArray1;
        delete[] strengthArrayLeftMiddle1;
        delete[] strengthArrayRight2;
        delete[] strengthArrayRight1;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArray2 = new StrengthInfo * [team2->getNumOfContestant()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArray1;
        delete[] strengthArrayLeftMiddle1;
        delete[] strengthArrayRight2;
        delete[] strengthArrayRight1;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        strengthArrayUniteRep = new StrengthInfo * [team1->getNumOfContestant()+team2->getNumOfContestant()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArray1;
        delete[] strengthArrayLeftMiddle1;
        delete[] strengthArrayRight2;
        delete[] strengthArrayRight1;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayMiddle1;
        delete[] strengthArrayLeft2;
        delete[] strengthArrayLeft1;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }

    mergeStrength(strengthArrayLeft1, team1->getLeftTreeStrength()->getNodeCount(), strengthArrayMiddle1,
                  team1->getMiddleTreeStrength()->getNodeCount(),strengthArrayLeftMiddle1);

    mergeStrength(strengthArrayLeftMiddle1,team1->getLeftTreeStrength()->getNodeCount() +team1->getMiddleTreeStrength()->getNodeCount(),
                  strengthArrayRight1, team1->getRightTreeStrength()->getNodeCount(), strengthArray1);


    mergeStrength(strengthArrayLeft2, team2->getLeftTreeStrength()->getNodeCount(), strengthArrayMiddle2,
                  team2->getMiddleTreeStrength()->getNodeCount(),strengthArrayLeftMiddle2);

    mergeStrength(strengthArrayLeftMiddle2,team2->getLeftTreeStrength()->getNodeCount() +team2->getMiddleTreeStrength()->getNodeCount(),
                  strengthArrayRight2, team2->getRightTreeStrength()->getNodeCount(), strengthArray2);


    mergeStrength(strengthArray1, team1->getNumOfContestant(), strengthArray2, team2->getNumOfContestant()
            ,strengthArrayUniteRep);

    delete[] strengthArrayLeft1;
    delete[] strengthArrayMiddle1;
    delete[] strengthArrayRight1;
    delete[] strengthArrayLeftMiddle1;
    delete[] strengthArray1;

    delete[] strengthArrayLeft2;
    delete[] strengthArrayMiddle2;
    delete[] strengthArrayRight2;
    delete[] strengthArrayLeftMiddle2;
    delete[] strengthArray2;

    Contestant** contestantArrayUniteRep;
    try{
        contestantArrayUniteRep = new Contestant * [team1->getNumOfContestant()+team2->getNumOfContestant()];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        delete[] contestantArray2;
        delete[] contestantArray1;
        return StatusType::ALLOCATION_ERROR;
    }

    mergeContestant(contestantArray1,team1->getNumOfContestant(),contestantArray2,team2->getNumOfContestant(),contestantArrayUniteRep  );

    for ( int i = 0 ; i < team2->getNumOfContestant() ; i++) {
        contestantArray2[i]->decreaseTeamNumAndArray(teamId2);
        contestantArray2[i]->decreaseTeamNumAndArray(teamId1);
        contestantArray2[i]->increaseTeamNumAndArray(teamId1);
    }

    delete[] contestantArray1;
    delete[] contestantArray2;

    int countRep= 0;
    for (int i = 0; i <team1->getNumOfContestant()+team2->getNumOfContestant()-1  ; ++i) {
        if (contestantArrayUniteRep[i]->get_contestantID() == contestantArrayUniteRep[i + 1]->get_contestantID()) {
            contestantArrayUniteRep[i] = nullptr;
            i++;
            countRep++;
        }
    }
    int newNumOfContestants = team1->getNumOfContestant()+team2->getNumOfContestant() - countRep;
    Contestant** contestantArrayUniteNoRep;
    try{
        contestantArrayUniteNoRep = new Contestant * [newNumOfContestants];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] contestantArrayUniteRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    for (int j=0, i = 0 ; i <team1->getNumOfContestant()+team2->getNumOfContestant() ; ++i) {
        if (contestantArrayUniteRep[i]!= nullptr) {
            contestantArrayUniteNoRep[j] = contestantArrayUniteRep[i];
            j++;
        }
    }

    for (int i = 0; i <team1->getNumOfContestant()+team2->getNumOfContestant()-1  ; ++i) {
        if ((strengthArrayUniteRep[i]->getStrengthFromInfo() == strengthArrayUniteRep[i+1]->getStrengthFromInfo()) &&
            (strengthArrayUniteRep[i]->getIdFromInfo() == strengthArrayUniteRep[i+1]->getIdFromInfo()) ) {
            strengthArrayUniteRep[i]= nullptr;
            i++;
        }
    }
    StrengthInfo** strengthArrayUniteNoRep;
    try{
        strengthArrayUniteNoRep = new StrengthInfo * [newNumOfContestants];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] contestantArrayUniteNoRep;
        delete[] contestantArrayUniteRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    for (int j=0, i = 0 ; i <team1->getNumOfContestant()+team2->getNumOfContestant() ; ++i) {
        if (strengthArrayUniteRep[i]!= nullptr) {
            strengthArrayUniteNoRep[j] = strengthArrayUniteRep[i];
            j++;
        }
    }
    delete[] contestantArrayUniteRep;

    int newNumOfContestantsLeft = 0,  newNumOfContestantsMiddle = 0, newNumOfContestantsRight = 0 ;

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

    for (int i = 0 ; i <newNumOfContestantsLeft ; ++i) {
        contestantArrayUniteNoRep[i]->getStrengthInfo()->setTree('L');
    }
    for (int i = newNumOfContestantsLeft ; i <newNumOfContestantsLeft+newNumOfContestantsMiddle ; ++i) {
        contestantArrayUniteNoRep[i]->getStrengthInfo()->setTree('M');
    }
    for (int i = newNumOfContestantsLeft+newNumOfContestantsMiddle ; i <newNumOfContestantsLeft+newNumOfContestantsMiddle
                                                                        +newNumOfContestantsRight; ++i) {
        contestantArrayUniteNoRep[i]->getStrengthInfo()->setTree('R');
    }

    StrengthInfo** newStrengthArrayLeft;
    try{
        newStrengthArrayLeft = new StrengthInfo * [newNumOfContestantsLeft];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] strengthArrayUniteNoRep;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    StrengthInfo** newStrengthArrayMiddle;
    try{
        newStrengthArrayMiddle = new StrengthInfo * [newNumOfContestantsMiddle];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] newStrengthArrayLeft;
        delete[] strengthArrayUniteNoRep;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    StrengthInfo** newStrengthArrayRight;
    try{
        newStrengthArrayRight = new StrengthInfo * [newNumOfContestantsRight];
    }
    catch (const std::bad_alloc &e)
    {
        delete[] newStrengthArrayMiddle;
        delete[] newStrengthArrayLeft;
        delete[] strengthArrayUniteNoRep;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    for (int il = 0, im = 0,ir = 0 , i = 0; i < newNumOfContestants ; ++i) {
        if ( strengthArrayUniteNoRep[i]->getTree() == 'L') {
            newStrengthArrayLeft[il] = strengthArrayUniteNoRep[i];
            il++;
        }
        else if ( strengthArrayUniteNoRep[i]->getTree() == 'M') {
            newStrengthArrayMiddle[im] = strengthArrayUniteNoRep[i];
            im++;
        }
        else {
            newStrengthArrayRight[ir] = strengthArrayUniteNoRep[i];
            ir++;
        }
    }
    delete[] strengthArrayUniteNoRep;


    delete team1->getLeftTreeStrength();
    team1->setLeftTreeStrength(nullptr);

    delete team1->getMiddleTreeStrength();
    team1->setMiddleTreeStrength(nullptr);

    delete team1->getRightTreeStrength();
    team1->setRightTreeStrength(nullptr);

    StrengthPairKey nullKey = StrengthPairKey(-1, -1);

    AVLTree<StrengthPairKey, StrengthInfo>* newLeftTreeStrength;
    try{
        newLeftTreeStrength = new AVLTree<StrengthPairKey, StrengthInfo>();
    }
    catch (const std::bad_alloc &e)
    {
        delete[] newStrengthArrayRight;
        delete[] newStrengthArrayMiddle;
        delete[] newStrengthArrayLeft;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        newLeftTreeStrength->buildTreeBeforeInsertArray(newNumOfContestantsLeft, nullKey);
    }
    catch (const std::bad_alloc &e)
    {
        delete newLeftTreeStrength;
        delete[] newStrengthArrayRight;
        delete[] newStrengthArrayMiddle;
        delete[] newStrengthArrayLeft;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    team1->setLeftTreeStrength(newLeftTreeStrength);

    AVLTree<StrengthPairKey, StrengthInfo>* newMiddleTreeStrength;
    try{
        newMiddleTreeStrength = new AVLTree<StrengthPairKey, StrengthInfo>();
    }
    catch (const std::bad_alloc &e)
    {
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] newStrengthArrayRight;
        delete[] newStrengthArrayMiddle;
        delete[] newStrengthArrayLeft;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        newMiddleTreeStrength->buildTreeBeforeInsertArray(newNumOfContestantsMiddle, nullKey);
    }
    catch (const std::bad_alloc &e)
    {
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] newStrengthArrayRight;
        delete[] newStrengthArrayMiddle;
        delete[] newStrengthArrayLeft;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    team1->setMiddleTreeStrength(newMiddleTreeStrength);

    AVLTree<StrengthPairKey, StrengthInfo>* newRightTreeStrength;
    try{
        newRightTreeStrength = new AVLTree<StrengthPairKey, StrengthInfo>();
    }
    catch (const std::bad_alloc &e)
    {
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] newStrengthArrayRight;
        delete[] newStrengthArrayMiddle;
        delete[] newStrengthArrayLeft;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        newRightTreeStrength->buildTreeBeforeInsertArray(newNumOfContestantsRight, nullKey);
    }
    catch (const std::bad_alloc &e)
    {
        delete newRightTreeStrength;
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] newStrengthArrayRight;
        delete[] newStrengthArrayMiddle;
        delete[] newStrengthArrayLeft;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    team1->setRightTreeStrength(newRightTreeStrength);
    int il =0 , im = 0 , ir = 0;
    team1->getLeftTreeStrength()->convertArrayToTree(team1->getLeftTreeStrength()->getRoot(),newStrengthArrayLeft, &il);
    team1->getMiddleTreeStrength()->convertArrayToTree(team1->getMiddleTreeStrength()->getRoot(),newStrengthArrayMiddle, &im);
    team1->getRightTreeStrength()->convertArrayToTree(team1->getRightTreeStrength()->getRoot(),newStrengthArrayRight, &ir);

    delete[] newStrengthArrayLeft;
    delete[] newStrengthArrayMiddle;
    delete[] newStrengthArrayRight;

    team1->setNumOfContestant(newNumOfContestants);
    team2->setNumOfContestant(0);

    delete team1->getLeftTreeID();
    team1->setLeftTreeID(nullptr);

    delete team1->getMiddleTreeID();
    team1->setMiddleTreeID(nullptr);

    delete team1->getRightTreeID();
    team1->setRightTreeID(nullptr);

    AVLTree<int, Contestant>* newLeftTreeID;
    try{
        newLeftTreeID = new AVLTree<int, Contestant>();
    }
    catch (const std::bad_alloc &e)
    {
        delete newRightTreeStrength;
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    try{
        newLeftTreeID->buildTreeBeforeInsertArray(newNumOfContestantsLeft, -1);
    }
    catch (const std::bad_alloc &e)
    {
        delete newLeftTreeID;
        delete newRightTreeStrength;
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    team1->setLeftTreeID(newLeftTreeID);

    AVLTree<int, Contestant>* newMiddleTreeID;
    try{
        newMiddleTreeID = new AVLTree<int, Contestant>();
    }
    catch (const std::bad_alloc &e)
    {
        delete newLeftTreeID;
        delete newRightTreeStrength;
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        newMiddleTreeID->buildTreeBeforeInsertArray(newNumOfContestantsMiddle, -1);
    }
    catch (const std::bad_alloc &e)
    {
        delete newMiddleTreeID;
        delete newLeftTreeID;
        delete newRightTreeStrength;
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }

    team1->setMiddleTreeID(newMiddleTreeID);

    AVLTree<int, Contestant>* newRightTreeID;
    try{
        newRightTreeID = new AVLTree<int, Contestant>();
    }
    catch (const std::bad_alloc &e)
    {
        delete newMiddleTreeID;
        delete newLeftTreeID;
        delete newRightTreeStrength;
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        newRightTreeID->buildTreeBeforeInsertArray(newNumOfContestantsRight, -1);
    }
    catch (const std::bad_alloc &e)
    {
        delete newRightTreeID;
        delete newMiddleTreeID;
        delete newLeftTreeID;
        delete newRightTreeStrength;
        delete newMiddleTreeStrength;
        delete newMiddleTreeStrength;
        delete newLeftTreeStrength;
        delete newLeftTreeStrength;
        delete[] contestantArrayUniteNoRep;
        delete[] strengthArrayUniteRep;
        delete[] strengthArray2;
        delete[] strengthArrayLeftMiddle2;
        delete[] strengthArrayRight2;
        delete[] strengthArrayMiddle2;
        delete[] strengthArrayLeft2;
        return StatusType::ALLOCATION_ERROR;
    }
    team1->setRightTreeID(newRightTreeID);

    int indexID=0;
    team1->getLeftTreeID()->convertArrayToTree(team1->getLeftTreeID()->getRoot(),contestantArrayUniteNoRep, &indexID);
    team1->getMiddleTreeID()->convertArrayToTree(team1->getMiddleTreeID()->getRoot(),contestantArrayUniteNoRep, &indexID);
    team1->getRightTreeID()->convertArrayToTree(team1->getRightTreeID()->getRoot(),contestantArrayUniteNoRep, &indexID);

    delete[] contestantArrayUniteNoRep;
    team1->setKeyAfterUnite();

    team1->setTeamStrength(team1->calcStrength());
    team1->calcAusterity();
    delete[] strengthArrayUniteRep;
    return remove_team(teamId2);

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
    int pointTeam2 = medalT2 + get_team_strength(teamId2).ans();
    if(pointTeam1 > pointTeam2){
        m_TeamTree->findKey(teamId1, m_TeamTree->getRoot())->getData()->getCountry()->countryWonMedal();
    }
    else if (pointTeam1 < pointTeam2){
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

    return (m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getAusterity());
}
