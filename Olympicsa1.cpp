#include "Olympicsa1.h"



Olympics::Olympics(){

}

Olympics::~Olympics(){


}
//all done except from try catch
StatusType Olympics::add_country(int countryId, int medals){
    if (countryId <= 0 || medals <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_countryTree->findKey(countryId, this->m_countryTree->getRoot()) == nullptr){
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
    this->m_countryTree->insertNodeToTree(node,this->m_countryTree->getRoot());
    return StatusType::SUCCESS;
}
//try catch???
StatusType Olympics::remove_country(int countryId){
    if(countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_countryTree->findKey(countryId, this->m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if((this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->getData()->get_numsContestant() != 0)
       || (this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->getData()->get_numsTeam() != 0)){
        return StatusType::FAILURE;
    }
    delete this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->getData();
    this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->setData(nullptr);
    this->m_countryTree->DeleteNodeFromTree(this->m_countryTree->getRoot(),countryId);
    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    return StatusType::FAILURE;
}

StatusType Olympics::remove_team(int teamId){
    return StatusType::FAILURE;
}
//try catchhhhhhh
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if (countryId <= 0 || contestantId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }
    if(this->m_contestantTree->findKey(contestantId,this->m_contestantTree->getRoot()) != nullptr){
        return StatusType::FAILURE;
    }
    if(this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    Country* curr = this->m_countryTree->findKey(countryId,this->m_countryTree->getRoot())->getData();
    Contestant* newContestant = new Contestant(contestantId, curr, sport,strength);
    if(newContestant == nullptr){//not sure
        return StatusType::ALLOCATION_ERROR;
    }
    Node<int,Contestant>* node = new Node<int,Contestant>(contestantId);
    if (node == nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    node->setData(newContestant);
    this->m_contestantTree->insertNodeToTree(node,this->m_contestantTree->getRoot());
    return StatusType::SUCCESS;
}
//try catch
StatusType Olympics::remove_contestant(int contestantId){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (this->m_contestantTree->findKey(contestantId, this->m_contestantTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if (this->m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData()->get_numTeam() > 0){
        return StatusType::FAILURE;
    }
    delete m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->getData();
    m_contestantTree->findKey(contestantId,m_contestantTree->getRoot())->setData(nullptr);
    m_contestantTree->DeleteNodeFromTree(m_contestantTree->getRoot(),contestantId);
    return StatusType::SUCCESS;
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    return StatusType::FAILURE;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    return StatusType::FAILURE;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
    if (contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
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
    if (this->m_countryTree->findKey(countryId,m_countryTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    return m_countryTree->findKey(countryId,m_countryTree->getRoot())->getData()->get_medals();

}

output_t<int> Olympics::get_team_strength(int teamId){
    return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
    return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    return StatusType::FAILURE;
}

output_t<int> Olympics::austerity_measures(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(m_TeamTree->findKey(teamId,m_TeamTree->getRoot()) == nullptr){
        return StatusType::FAILURE;
    }
    if(this->m_TeamTree->findKey(teamId,m_TeamTree->getRoot())->getData()->getNumOfContestant < 3){
        return StatusType::FAILURE;
    }

    return 0;
}


