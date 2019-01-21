#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME JOKER


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  //Bottom, BR, Right, RT, Top, TL, Left, LB,
 
  typedef vector <vector <int> > _MD;
  typedef vector <vector <bool> > _MV;
  typedef vector <vector <Pos> > _MP;
  typedef vector <vector <Pos> > V_CITY;
  typedef vector<int> VE;
  _MD aigua,city_matriu,city,gasolina;
  V_CITY cities;
  vector <int> dist_2_1,dist_2_2;
  vector <_MD> c;


  /* TRUE if position p is adjacent to Station, FALSE if not */
  bool adja(Pos p){
    for(int i = 0; i < 8; ++i){
      if(pos_ok(p+Dir(i)) and cell(p+Dir(i)).type == Station) return true;
    }
    return false;
  }

 	/* TRUE if there is no other enemy car willing to kill a warrior */
  bool kill_warrior(Pos p){
	  for(int i = 0; i < 8; ++i){
	    Pos aux = p + Dir(i);
	    if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Car and unit(cell(aux).id).player != me() and cell(aux).type != City) return false;
	  }
	  return true;
  }
  
  /* TRUE if there is an enemy warrior in distance 2 */
  bool find_warrior(Pos act){
    if(pos_ok(act) and cell(act).type == Road) return true;
      for(int i = 0; i < 24; ++i){
        Pos voltant; voltant.i = act.i + dist_2_1[i]; voltant.j = act.j + dist_2_2[i];
        if(pos_ok(voltant) and cell(voltant).type == Road){
          return true;
        }
      }
      return false;
  }

  /* Dijkstra algorithm to find gas station */
  void dijkstra_fuel(int id, Pos p, _MV& stepped){
    _MD dist(60,vector<int>(60,65));
    _MV visited(60,vector<bool>(60,false));
    dist[p.i][p.j] = 0; visited[p.i][p.j] = true;
    vector < vector< pair<Pos,Dir> > > prev(60, vector< pair<Pos,Dir> >(60));
    priority_queue < pair<int,Pos>, vector<pair<int,Pos> >, greater<pair<int,Pos>> > c;
    c.push(make_pair(0,p));
    bool found = false;
    Pos res;
    while(not c.empty() and not found){
      Pos aux = c.top().second; c.pop();
      if(pos_ok(aux) and adja(aux) and not stepped[aux.i][aux.j] and (cell(aux).id == -1 or unit(cell(aux).id).type != Car)) {
        res = aux;
        found = true;
      }
      bool first_step = true;
      for(int i = 0; i < 8; ++i){
        if(first_step){
          Pos voltant = aux + Dir(i);
	        if(pos_ok(voltant) and cell(voltant).type != Desert and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall and 
	        	cell(voltant).type != Station and kill_warrior(voltant) and (cell(voltant).id == -1 or unit(cell(voltant).id).type != Car) and not stepped[voltant.i][voltant.j] and
	        	not visited[voltant.i][voltant.j]){
		          if(dist[voltant.i][voltant.j] > dist[aux.i][aux.j] + 1){
		            dist[voltant.i][voltant.j] = dist[aux.i][aux.j] + 1;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = aux;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
		          }
	        }
	        if(pos_ok(voltant) and cell(voltant).type != Road and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall 
	        	and cell(voltant).type != Station and kill_warrior(voltant) and (cell(voltant).id == -1 or unit(cell(voltant).id).type != Car ) and not stepped[voltant.i][voltant.j]
	        	and not visited[voltant.i][voltant.j]){
		          if(dist[voltant.i][voltant.j] > dist[aux.i][aux.j] + 4){
		            dist[voltant.i][voltant.j] = dist[aux.i][aux.j] + 4;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = aux;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
		          }
	        } 
        }
        else{
          Pos voltant = aux + Dir(i);
        	if(pos_ok(voltant) and cell(voltant).type != Desert and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall and 
        		cell(voltant).type != Station and (cell(voltant).id == -1 or  unit(cell(voltant).id).type != Car) and not stepped[voltant.i][voltant.j] and
        		not visited[voltant.i][voltant.j]){
          		if(dist[voltant.i][voltant.j] > dist[aux.i][aux.j] + 1){
		            dist[voltant.i][voltant.j] = dist[aux.i][aux.j] + 1;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = aux;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
	          }
        	}
	        if(pos_ok(voltant) and cell(voltant).type != Road and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall 
	        	and cell(voltant).type != Station and (cell(voltant).id == -1 or  unit(cell(voltant).id).type != Car) and not stepped[voltant.i][voltant.j]
	        	and not visited[voltant.i][voltant.j]){
		          if(dist[voltant.i][voltant.j] > dist[aux.i][aux.j] + 4){
		            dist[voltant.i][voltant.j] = dist[aux.i][aux.j] + 4;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = aux;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
		          }
	        } 
        }   
        if(i == 7) first_step = false;     
      }
    }
    if(found){
      while(prev[res.i][res.j].first != p) res = prev[res.i][res.j].first;
      command(id, prev[res.i][res.j].second);
      stepped[res.i][res.j] = true;
      return;
    } 
  }


  
	/*Dijkstra algorithm to find enemy warriors */
	bool dijkstra_find_warrior(int id,Pos p,_MV& stepped){
	  _MD dist(60,vector<int>(60,9999999));
	  _MV visited(60,vector<bool>(60,false));
	  dist[p.i][p.j] = 0; visited[p.i][p.j] = true;
	  vector < vector< pair<Pos,Dir> > > prev(60, vector< pair<Pos,Dir> >(60));
	  priority_queue < pair<int,Pos>, vector<pair<int,Pos> >, greater<pair<int,Pos>> > c;
	  c.push(make_pair(0,p));
	  bool found = false;
	  Pos res;
	  while(not c.empty() and not found){
	    Pos act = c.top().second; c.pop();
	    if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Warrior and unit(cell(act).id).player != me() and find_warrior(act) and not stepped[act.i][act.j]) {
	      res = act;
	      found = true;
	    }
	    bool first_step = true;
	    for(int i = 0; i < 8; ++i){
	      if(first_step){
	        Pos voltant = act + Dir(i);
	      	if(pos_ok(voltant) and cell(voltant).type != Desert and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall and 
	        	cell(voltant).type != Station and kill_warrior(voltant) and (cell(voltant).id == -1 or  (unit(cell(voltant).id).type != Car and unit(cell(voltant).id).player != me()) ) and not stepped[voltant.i][voltant.j] and
	       		not visited[voltant.i][voltant.j]){
		          if(dist[voltant.i][voltant.j] > dist[act.i][act.j] + 1){
		            dist[voltant.i][voltant.j] = dist[act.i][act.j] + 1;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = act;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
		          }
	        }
	        if(pos_ok(voltant) and cell(voltant).type != Road and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall 
	          and cell(voltant).type != Station and kill_warrior(voltant) and (cell(voltant).id == -1 or (unit(cell(voltant).id).type != Car and unit(cell(voltant).id).player != me())) and not stepped[voltant.i][voltant.j]
	          and not visited[voltant.i][voltant.j]){
		          if(dist[voltant.i][voltant.j] > dist[act.i][act.j] + 4){
		            dist[voltant.i][voltant.j] = dist[act.i][act.j] + 4;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = act;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
		          }
	        } 
	      }
	      else{
	        Pos voltant = act + Dir(i);
	        if(pos_ok(voltant) and cell(voltant).type != Desert and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall and 
	        	cell(voltant).type != Station and (cell(voltant).id == -1 or  (unit(cell(voltant).id).type != Car and unit(cell(voltant).id).player != me()) ) and not stepped[voltant.i][voltant.j] and
	         	not visited[voltant.i][voltant.j]){
		          if(dist[voltant.i][voltant.j] > dist[act.i][act.j] + 1){
		            dist[voltant.i][voltant.j] = dist[act.i][act.j] + 1;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = act;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
		          }
	        }
	        if(pos_ok(voltant) and cell(voltant).type != Road and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall 
	         	and cell(voltant).type != Station and (cell(voltant).id == -1 or(unit(cell(voltant).id).type != Car and unit(cell(voltant).id).player != me())) and not stepped[voltant.i][voltant.j]
	         	and not visited[voltant.i][voltant.j]){
		          if(dist[voltant.i][voltant.j] > dist[act.i][act.j] + 4){
		            dist[voltant.i][voltant.j] = dist[act.i][act.j] + 4;
		            visited[voltant.i][voltant.j] = true;
		            prev[voltant.i][voltant.j].first = act;
		            prev[voltant.i][voltant.j].second = Dir(i);
		            c.push(make_pair(dist[voltant.i][voltant.j],voltant));
		          }
	        } 
	      }   
	      if(i == 7 ) first_step = false;     
	    }
	  }
	  if(found){
	    while(prev[res.i][res.j].first != p) res = prev[res.i][res.j].first;
	    command(id, prev[res.i][res.j].second);
	    stepped[res.i][res.j] = true;
	    return true;
	  }
	  return false; 
	}


 Dir direccio(const _MP& m, Pos destinacio, Pos inici){
    int i = destinacio.i;
    int j = destinacio.j;
    while (m[i][j].i != inici.i or m[i][j].j != inici.j){
        int aux = i;
        i = m[i][j].i;
        j = m[aux][j].j;
    }
    if(i-inici.i == -1 and j-inici.j == -1) return TL;
    if(i-inici.i == -1 and j-inici.j == 0) return Top;
    if(i-inici.i == -1 and j-inici.j == 1) return RT;
    if(i-inici.i == 0 and j-inici.j == 1) return Right;
    if(i-inici.i == 1 and j-inici.j == 1) return BR;
    if(i-inici.i == 1 and j-inici.j == 0) return Bottom;
    if(i-inici.i == 1 and j-inici.j == -1) return LB;
    return Left;
 }


  bool adja1(Pos p){
    for(int i = 0; i < 8; ++i){
      if(pos_ok(p+Dir(i)) and cell(p+Dir(i)).type == Road){
          return true;
      }
    }
    return false;
  }


  
  /*Nearest road next to an enemy city */
  Pos nearest_city(_MP& m, Pos p, vector <bool> & checked, _MV& stepped){
    _MV visited(60, vector<bool>(60,false));
    queue <Pos> c_no_visitat;
    Pos initial = p;
    c_no_visitat.push(initial);
    visited[p.i][p.j] = true; 
    while(not c_no_visitat.empty()){
      Pos aux = c_no_visitat.front(); c_no_visitat.pop();
      if(pos_ok(aux)){
        for(int i = 0; i < 8 ; ++i){
          Pos aux1 = aux + Dir(i);
          if(pos_ok(aux1)){
            if(i == 0){
              Pos aux2 = aux1 + Dir(0);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]){
                checked[city_matriu[aux2.i][aux2.j]] = true;
                return aux;
              }
            }
            else if(i == 1){
              for(int j = 0; j < 3 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                  checked[city_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
            }
            else if(i == 2){
              Pos aux2 = aux1 + Dir(2);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                checked[city_matriu[aux2.i][aux2.j]] = true;
                return aux;}
            }
            else if(i == 3){
              for(int j = 2; j < 5 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                  checked[city_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
            }
            else if(i == 4){
              Pos aux2 = aux1 + Dir(4);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                checked[city_matriu[aux2.i][aux2.j]] = true;
                return aux;}
            }
            else if(i == 5){
              for(int j = 4; j < 7 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                  checked[city_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
            }
            else if(i == 6){
              Pos aux2 = aux1 + Dir(6);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                checked[city_matriu[aux2.i][aux2.j]] = true;
                return aux;}
            }
            else if(i == 7){
              for(int j = 6; j < 8 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                 checked[city_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
              Pos aux2 = aux1 + Dir(0);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not checked[city_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                checked[city_matriu[aux2.i][aux2.j]] = true;
                return aux;}
            }
          }
        }
      } 
      for(int i = 0; i < 8; ++i){
        Pos voltant = aux + Dir(i);
        if(pos_ok(voltant) and cell(voltant).type != Wall and cell(voltant).type != Water and not stepped[voltant.i][voltant.j] and cell(voltant).type != City and cell(voltant).type != Station and cell(voltant).type != Desert
        	and not visited[voltant.i][voltant.j] and (cell(voltant).id == -1 or (unit(cell(voltant).id).type != Car))){
          	visited[voltant.i][voltant.j] = true;
          	m[voltant.i][voltant.j] = aux;
          	c_no_visitat.push(voltant);
        }
      }
    }
    return p;
  }

  void i_move_car(int id, Pos p, _MV& stepped, _MP& m, vector <bool>& checked){
    for(int j = 0; j < 8; ++j){
      Pos aux = p + Dir(j);
      if(pos_ok(aux) and cell(aux).id != -1 and (cell(aux).type == Road or cell(aux).type == Desert) and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me() and kill_warrior(aux) and not stepped[aux.i][aux.j]){
        command(id,Dir(j)); stepped[aux.i][aux.j] = true; return;
      }
    }  
    if(unit(id).food <= 30){
      dijkstra_fuel(id,p,stepped);         
    }
    else{
      if(not dijkstra_find_warrior(id,p,stepped)){
        Pos res = nearest_city(m,p,checked,stepped);
        if(res != p){
          Dir d = direccio(m,res,p);
          command(id,d);
          Pos aux1 = p + d; stepped[aux1.i][aux1.j] = true;
        }
      } 
  	}
  }
      
  
  void move_car(_MV & stepped){
    vector<int> C = cars(me());
    _MP m(60,vector<Pos>(60));
    vector <bool> checked(8,false);
    for(int id : C){
      if(can_move(id)){
        Pos p = unit(id).pos;
        i_move_car(id,p,stepped,m,checked);
      } 
      else stepped[unit(id).pos.i][unit(id).pos.j] = true; 
    }  
  }
  
  /*check that the nearest car is at least far away from distance 2 */
	bool radar_cotxe(Pos p){
	  queue < pair<Pos,int>> c;
	  _MV visited(60,vector <bool>(60,false));
	  c.push(make_pair(p,0));
	  visited[p.i][p.j] = true;
	  while(not c.empty() and c.front().second <= 4){
	    Pos act = c.front().first; int dd = c.front().second + 1; c.pop();
	    if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Car and unit(cell(act).id).player != me() and cell(act).type == Road and unit(cell(act).id).food > 4) return true;
	    else if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Car and unit(cell(act).id).player != me() and cell(act).type == Desert and adja1(act)) return true;
	    else if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Car and unit(cell(act).id).player != me() and cell(act).type == Desert and dd-1 <= 1) return true;
	    for(int i = 0; i < 8; ++i){
	      Pos voltant = act + Dir(i);
	      if(pos_ok(voltant) and not visited[voltant.i][voltant.j] and (cell(voltant).type == Desert or cell(voltant).type == Road)){
	        visited[voltant.i][voltant.j] = true;
	        c.push(make_pair(voltant,dd));
	      }
	    } 
	  }
	  return false;
	}


	/*check wether the position p is safe or not (warrior)*/
	bool see_car(Pos p){
		if( cell(p).type == Road or (cell(p).type == Desert and adja1(p))){
			if(radar_cotxe(p)) return true;
		}
	  for(int i = 0; i < 8; ++i){
	    Pos p1 = p + Dir(i);
	    if(pos_ok(p1) and cell(p1).id != -1 and unit(cell(p1).id).type == Car and unit(cell(p1).id).player != me()) return true;
	  }
	  return false;
	}

	/* bfs algorithm to find the shortest distance to reach water */
  void bfs_water(_MD& m, Pos initial){
    _MV visited(60, vector<bool>(60,false));
    queue < pair<Pos,int> > c_no_visitat;
    c_no_visitat.push(make_pair(initial,0));
    visited[initial.i][initial.j] = true; m[initial.i][initial.j] = 0;
    while(not c_no_visitat.empty()){
      Pos aux = c_no_visitat.front().first; int dd = c_no_visitat.front().second + 1; c_no_visitat.pop();
      for(int i = 0; i < 8; ++i){
        Pos voltant = aux + Dir(i);
        if(pos_ok(voltant) and cell(voltant).type != Wall and cell(voltant).type != Station and not visited[voltant.i][voltant.j]){
          visited[voltant.i][voltant.j] = true;
          if(m[voltant.i][voltant.j] > dd){
            m[voltant.i][voltant.j] = dd;
            c_no_visitat.push(make_pair(voltant,dd));
          }
        }
      }
    }
  }

  /* bfs algorithm to find the shortest distance to reach city */
  void bfs_city(_MD& m, Pos initial){
    _MV visited(60, vector<bool>(60,false));
    queue < pair<Pos,int> > c_no_visitat;
    c_no_visitat.push(make_pair(initial,0));
    visited[initial.i][initial.j] = true; m[initial.i][initial.j] = 0;
    while(not c_no_visitat.empty()){
      Pos aux = c_no_visitat.front().first; int dd = c_no_visitat.front().second + 1; c_no_visitat.pop();
      for(int i = 0; i < 8; ++i){
        Pos voltant = aux + Dir(i);
        if(pos_ok(voltant) and cell(voltant).type != Wall and cell(voltant).type != Water and cell(voltant).type != Station and not visited[voltant.i][voltant.j]){
          visited[voltant.i][voltant.j] = true;
          if(m[voltant.i][voltant.j] > dd){
            m[voltant.i][voltant.j] = dd;
            c_no_visitat.push(make_pair(voltant,dd));
          }
        }
      }
    }
  }  
 
  
  void start_city(V_CITY& cities, _MV& m_citi, _MD& city_matriu, int id, Pos p){
    if(not pos_ok(p) or cell(p).type != City or m_citi[p.i][p.j]) return;
    m_citi[p.i][p.j] = true;
    cities[id].push_back(p);
    city_matriu[p.i][p.j] = id;
    for(int i = 0; i < 8; ++i) start_city(cities,m_citi,city_matriu, id, p + Dir(i));
  }
  
  
  void count_warriors(vector <vector<int> >& players, V_CITY& c){
    for(int i = 0; i < 8; ++i){
      for(auto w : c[i]){
        // si hi ha algun puto jugador
        if(cell(w).id != -1){
          int p = unit(cell(w).id).player;
          ++ players[i][p];
        }
      }
    }
  }

  bool pos_safe_warrior(Pos p){
    for(int i = 0; i < 8; ++i){
      Pos aux = p + Dir(i);
      if(pos_ok(aux) and cell(aux).id != -1 and cell(aux).type == City and unit(cell(aux).id).player != me() ) return false;
    }
    return true;
  }

  /*go to the nearest enemy city under distance 10*/
  bool enemy_city(int city, int id, Pos p, _MD& m,_MV& stepped,vector <vector <int> >& players){
    if(m[p.i][p.j] > 9) return false;
    //només procedim si veiem q la city no es nostra i q no hi ha més de 2 soldats enemics
    for(int i = 0; i < 4; ++i){
      if(i != me()){
        if(cell(cities[city][0]).owner == me()) return false;
        else if(players[city][i] > 2 and players[city][i]+1 < players[city][me()]) return false;
      }
    }
         
    for(int i = 0; i < 8; ++i){
      Pos aux = p +Dir(i);
      if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
        if(not see_car(p)){
          command(id, Dir(i));
          return true;
        }
      }
    }
    for(int j = 0; j < 9; ++j){
      Pos aux = p + Dir(j);
      if(pos_ok(aux) and m[aux.i][aux.j] < m[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
        command(id,Dir(j));
        stepped[aux.i][aux.j] = true; ++players[city][me()];
        return true;
      }
    }
               
    for(int j = 0; j < 9; ++j){
      Pos aux = p + Dir(j);
      if(pos_ok(aux) and m[aux.i][aux.j] == m[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
        command(id,Dir(j));
        stepped[aux.i][aux.j] = true; ++players[city][me()];
        return true;
      }
    }
            
    for(int j = 0; j < 9; ++j){
      Pos aux = p + Dir(j);
      if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
      	command(id,Dir(j));
        stepped[aux.i][aux.j] = true; ++players[city][me()];
        return true;
      }
    }
              
    for(int j = 0; j < 9; ++j){
      Pos aux = p + Dir(j);
      if(pos_ok(aux) and m[aux.i][aux.j] < m[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car))  and not stepped[aux.i][aux.j]){
        command(id,Dir(j));
        stepped[aux.i][aux.j] = true; ++players[city][me()];
        return true;
      }
    }
               
    for(int j = 0; j < 9; ++j){
      Pos aux = p + Dir(j);
      if(pos_ok(aux) and m[aux.i][aux.j] == m[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not stepped[aux.i][aux.j]){
        command(id,Dir(j));
        stepped[aux.i][aux.j] = true; ++players[city][me()];
        return true;
      }
    }
            
    for(int j = 0; j < 9; ++j){
      Pos aux = p + Dir(j);
      if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and  not stepped[aux.i][aux.j]){
      	command(id,Dir(j));
        stepped[aux.i][aux.j] = true; ++players[city][me()];
        return true;
      }
    }
    command(id, None);  
    stepped[p.i][p.j] = true; ++players[city][me()];
  	return true;    
  }



  void i_move_warriors(int id, Pos p, _MV& stepped,vector <vector<int> >& players,vector <bool>& city_enviat){
    if(unit(id).water <= 15 or unit(id).water <= aigua[p.i][p.j]+3){
      for(int i = 0; i < 8; ++i){
        Pos aux = p +Dir(i);
        if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
          if(not see_car(p)){
           	command(id, Dir(i));
            return;
          }
        }
      }

      for(int j = 0; j < 8; ++j){
        Pos aux = p + Dir(j);
        if(pos_ok(aux) and aigua[aux.i][aux.j] < aigua[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
          command(id,Dir(j));
          stepped[aux.i][aux.j] = true;
          return;
        }
      }
      
      for(int j = 0; j < 9; ++j){
        Pos aux = p + Dir(j);
        if(pos_ok(aux) and aigua[aux.i][aux.j] == aigua[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
          command(id,Dir(j));
          stepped[aux.i][aux.j] = true;
          return;
        }
      }
         
      for(int j = 0; j < 9; ++j){
        Pos aux = p + Dir(j);
        if(pos_ok(aux) and aigua[aux.i][aux.j] < unit(id).water and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
          command(id,Dir(j));
          stepped[aux.i][aux.j] = true;
          return;
        } 
      }
      for(int j = 0; j < 9; ++j){
        Pos aux = p + Dir(j);
        if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and  not see_car(aux) and not stepped[aux.i][aux.j]){
          command(id,Dir(j));
          stepped[aux.i][aux.j] = true;
          return;
        } 
      }
      for(int i = 0; i < 8; ++i){
        Pos aux = p +Dir(i);
        if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
          if(not see_car(p)){
            command(id, Dir(i));
            return;
          }
        }
      }

      for(int j = 0; j < 8; ++j){
        Pos aux = p + Dir(j);
        if(pos_ok(aux) and aigua[aux.i][aux.j] < aigua[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not stepped[aux.i][aux.j]){
          command(id,Dir(j));
          stepped[aux.i][aux.j] = true;
          return;
        }
      }
      
      for(int j = 0; j < 9; ++j){
        Pos aux = p + Dir(j);
        if(pos_ok(aux) and aigua[aux.i][aux.j] == aigua[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and  not stepped[aux.i][aux.j]){
          command(id,Dir(j));
          stepped[aux.i][aux.j] = true;
          return;
        }
      }
      
      for(int j = 0; j < 9; ++j){
         Pos aux = p + Dir(j);
         if(pos_ok(aux) and aigua[aux.i][aux.j] < unit(id).water and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and  not stepped[aux.i][aux.j]){
            command(id,Dir(j));
            stepped[aux.i][aux.j] = true;
            return;
          } 
        }

      for(int j = 0; j < 9; ++j){
        Pos aux = p + Dir(j);
        if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and   not stepped[aux.i][aux.j]){
          command(id,Dir(j));
          stepped[aux.i][aux.j] = true;
          return;
        } 
      }                  
      command(id,None);
      stepped[p.i][p.j] = true;  
      return;                            
    }
    else{
      if(cell(p).type != City and cell(p).type != Wall and cell(p).type != Water and cell(p).type != Station){  
        for(int i = 0; i < 8; ++i){
          Pos aux = p +Dir(i);
          if(pos_ok(aux) and cell(aux).type == City and cell(aux).id == -1 and not stepped[aux.i][aux.j]){
            command(id, Dir(i));
            stepped[aux.i][aux.j] = true;
            return;
          } 
        }
        for(int i = 0; i < 8; ++i){
        	Pos aux = p +Dir(i);
          if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
            if(not see_car(p)){
              command(id, Dir(i));
              return;
            }
          }
        }   
        vector < pair<int,int> > sequence_city(8);
        for(int i = 0; i < 8; ++i){
          sequence_city[i].first = c[i][p.i][p.j];
          sequence_city[i].second = i;
        }
        sort(sequence_city.begin(),sequence_city.end());
        bool gone = false;
        for(int i = 0; i < 8 and not gone; ++i){
          gone = enemy_city(sequence_city[i].second,id,p,c[sequence_city[i].second],stepped,players);
        }
        if(not gone){
          for(int i = 0; i < 8; ++i){
	          Pos aux = p +Dir(i);
	          if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
	            if(not see_car(p)){
	              command(id, Dir(i));
	              return;
	            }
	          }
          }              
          for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and city[aux.i][aux.j] < city[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).type != Car and unit(cell(aux).id).player != me())) and not see_car(aux) and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
            }
          }
                    
        	for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and city[aux.i][aux.j] == city[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
             }
          }
        
          for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not see_car(aux) and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
            }
          }

          for(int i = 0; i < 8; ++i){
            Pos aux = p +Dir(i);
            if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
              if(not see_car(p)){
                command(id, Dir(i));
                return;
              }
            }
          }

          for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and city[aux.i][aux.j] < city[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).type != Car and unit(cell(aux).id).player != me())) and  not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
            }
          }
                    
          for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and city[aux.i][aux.j] == city[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
            }
          }
        
          for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and  not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
            }
          }
          command(id, None);  
          stepped[p.i][p.j] = true;
          return;
        }                       
    	}
      else if(cell(p).type == City){
        for(int i = 0; i < 8; ++i){
          Pos aux = p +Dir(i);
          if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
            if(cell(aux).type == City){
              if(unit(id).food - unit(cell(aux).id).food >= 5){
                command(id,Dir(i));
                return;
              }
            }
          }
        }

        for(int i = 0; i < 8; ++i){
          Pos aux = p +Dir(i);
          if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
            if(cell(aux).type == Desert){
              command(id,Dir(i));
              return;
            }
          }
        }    

        for(int i = 0; i < 8; ++i){
          Pos aux = p +Dir(i);
          if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
            if(cell(aux).type == City){
              if( unit(cell(aux).id).food - unit(id).food <= 5){
                command(id,Dir(i));
                return;
              }
            }
          }
        }

        for(int j = 0; j < 9; ++j){
          Pos aux = p + Dir(j);
          if(pos_ok(aux) and city[aux.i][aux.j] == city[p.i][p.j] and (cell(aux).id == -1) and pos_safe_warrior(aux) and not stepped[aux.i][aux.j]){
            command(id,Dir(j));
            stepped[aux.i][aux.j] = true;
            return;
          }
        }
   
        for(int j = 0; j < 9; ++j){
          Pos aux = p + Dir(j);
          if(pos_ok(aux) and city[aux.i][aux.j] == city[p.i][p.j] and (cell(aux).id == -1) and not stepped[aux.i][aux.j]){
            command(id,Dir(j));
            stepped[aux.i][aux.j] = true;
            return;
          }
        }

        for(int j = 0; j < 9; ++j){
          Pos aux = p + Dir(j);
          if(pos_ok(aux) and city[aux.i][aux.j] == city[p.i][p.j] and (cell(aux).id != -1 and unit(id).food > unit(cell(aux).id).food +5) and not stepped[aux.i][aux.j]){
            command(id,Dir(j));
            stepped[aux.i][aux.j] = true;
            return;
          }
        } 

        for(int j = 0; j < 9; ++j){
          Pos aux = p + Dir(j);
          if(pos_ok(aux) and city[aux.i][aux.j] == 1 and (cell(aux).id != -1) and not stepped[aux.i][aux.j]){
            command(id,Dir(j));
            stepped[aux.i][aux.j] = true;
            return;
          }
        } 
      }
    }
  }

  void move_warriors(_MV& stepped) {
    if (round()% 4 != me()) return; 
    VE W = warriors(me());
    int n = W.size();
    VE perm = random_permutation(n);
    _MP m(60,vector<Pos>(60));
    vector < vector<int> > players(8,vector<int>(4,0));
    count_warriors(players,cities);
    vector <bool> city_enviat(8,false);
    for (int i = 0; i < n; ++i) {
      int id = W[perm[i]];
      Pos p = unit(id).pos;
      i_move_warriors(id,p,stepped,players,city_enviat);
    }
  }
  


  void play () {
    //initialitzacions
    if(round() == 0){
      aigua = _MD(60,vector <int>(60,61));
      city = _MD(60,vector <int>(60,61));
      _MV m_citi(60,vector <bool>(60,false));
      city_matriu = _MD(60,vector <int>(60,9));
      c = vector <_MD>(8,_MD(60,vector <int>(60,61)));
      dist_2_1 = dist_2_2 = vector <int>(24);
      dist_2_2[0] = -1;dist_2_2[1] = 0;dist_2_2[2] = 1;dist_2_2[3] = 1;dist_2_2[4] = 1;dist_2_2[5] = 0;dist_2_2[6] = -1;dist_2_2[7] = -1;dist_2_2[8] = -2;dist_2_2[9] = -1;dist_2_2[10] = 0;dist_2_2[11] = 1;dist_2_2[12] = 2;dist_2_2[13] = 2;dist_2_2[14] = 2;dist_2_2[15] = 2;dist_2_2[16] = 2;dist_2_2[17] = 1;dist_2_2[18] = 0;dist_2_2[19] = -1;dist_2_2[20] = -2;dist_2_2[21] = -2;dist_2_2[22] = -2;dist_2_2[23] = -2;
      dist_2_1[0] = -1;dist_2_1[1] = -1;dist_2_1[2] = -1;dist_2_1[3] = 0;dist_2_1[4] = 1;dist_2_1[5] = 1;dist_2_1[6] = 1;dist_2_1[7] = 0;dist_2_1[8] = -2;dist_2_1[9] = -2;dist_2_1[10] = -2;dist_2_1[11] = -2;dist_2_1[12] = -2;dist_2_1[13] = -1;dist_2_1[14] = 0;dist_2_1[15] = 1;dist_2_1[16] = 2;dist_2_1[17] = 2;dist_2_1[18] = 2;dist_2_1[19] = 2;dist_2_1[20] = 2;dist_2_1[21] = -1;dist_2_1[22] = 0;dist_2_1[23] = 1;
      cities = V_CITY(8);
      int id = 0;
      for(int i = 0; i < 60; ++i){
        for(int j = 0; j < 60; ++j){
          Pos p; p.i = i; p.j = j;
          if(cell(i,j).type == Water) bfs_water(aigua,p);
          else if(cell(i,j).type == City){
            bfs_city(city,p);
            if(not m_citi[i][j]){
              start_city(cities,m_citi,city_matriu,id,p);
              ++id;
            }
          }      
        }
      }

      for(int i = 0; i < 8; ++i){
        for(Pos p : cities[i]){
          bfs_city(c[i],p);
        }
      }
    }

    _MV stepped(60, vector<bool>(60,false)); // evitar que es matin entre ells
    move_warriors(stepped);
    move_car(stepped); 
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);