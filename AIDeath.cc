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
 
  typedef vector <vector <int> > matrix_distancia;
  typedef vector <vector <bool> > matrix_visitat;
  typedef vector <vector <Pos> > matrix_posicio;
  typedef vector <vector <Pos> > V_CITY;
  typedef vector<int> VE;
  matrix_distancia aigua,ciutat_matriu,ciutat,gasolina;
  V_CITY cities;
  vector <int> dist_2_1,dist_2_2;
  vector <matrix_distancia> c;
   // despres es posa en el play
  /**
   * Play method, invoked once per each round.
   */
  bool adja(Pos p){
    for(int i = 0; i < 8; ++i){
      if(pos_ok(p+Dir(i)) and cell(p+Dir(i)).type == Station) return true;
    }
    return false;
  }
  /* Inicialització */
 
  bool eatable(Pos p){
  for(int i = 0; i < 8; ++i){
    Pos aux = p + Dir(i);
    if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Car and unit(cell(aux).id).player != me() and cell(aux).type != City ) return false;
  }
  return true;
  }
  
  //si soldat erstà a distancia 2 de carretera.
  bool soldat_a_vista(Pos act){
    if(pos_ok(act) and cell(act).type == Road) return true;
      for(int i = 0; i < 24; ++i){
        Pos voltant; voltant.i = act.i + dist_2_1[i]; voltant.j = act.j + dist_2_2[i];
        if(pos_ok(voltant) and cell(voltant).type == Road){
          return true;
        }
      }
      return false;
  }

  void dijkstra_dist_gas(int id,Pos p,matrix_visitat& stepped){
    matrix_distancia dist(60,vector<int>(60,65));
    matrix_visitat visited(60,vector<bool>(60,false));
    dist[p.i][p.j] = 0; visited[p.i][p.j] = true;
    vector < vector< pair<Pos,Dir> > > prev(60, vector< pair<Pos,Dir> >(60));
    priority_queue < pair<int,Pos>, vector<pair<int,Pos> >, greater<pair<int,Pos>> > cua;
    cua.push(make_pair(0,p));
    bool trobat = false;
    Pos res;
    while(not cua.empty() and not trobat){
      Pos aux = cua.top().second; cua.pop();
      if(pos_ok(aux) and adja(aux) and not stepped[aux.i][aux.j] and (cell(aux).id == -1 or unit(cell(aux).id).type != Car)) {
        res = aux;
        trobat = true;
      }
        bool first_step = true;
        for(int i = 0; i < 8; ++i){
          if(first_step){
            Pos voltant = aux + Dir(i);
          if(pos_ok(voltant) and cell(voltant).type != Desert and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall and 
          cell(voltant).type != Station and eatable(voltant) and (cell(voltant).id == -1 or unit(cell(voltant).id).type != Car) and not stepped[voltant.i][voltant.j] and
          not visited[voltant.i][voltant.j]){
            if(dist[voltant.i][voltant.j] > dist[aux.i][aux.j] + 1){
              dist[voltant.i][voltant.j] = dist[aux.i][aux.j] + 1;
              visited[voltant.i][voltant.j] = true;
              prev[voltant.i][voltant.j].first = aux;
              prev[voltant.i][voltant.j].second = Dir(i);
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
            }
          }
          if(pos_ok(voltant) and cell(voltant).type != Road and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall 
          and cell(voltant).type != Station and eatable(voltant) and (cell(voltant).id == -1 or unit(cell(voltant).id).type != Car ) and not stepped[voltant.i][voltant.j]
          and not visited[voltant.i][voltant.j]){
            if(dist[voltant.i][voltant.j] > dist[aux.i][aux.j] + 4){
              dist[voltant.i][voltant.j] = dist[aux.i][aux.j] + 4;
              visited[voltant.i][voltant.j] = true;
              prev[voltant.i][voltant.j].first = aux;
              prev[voltant.i][voltant.j].second = Dir(i);
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
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
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
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
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
            }
          } 
          }   
          if(i == 7) first_step = false;     
        }
    
    }
    if(trobat){
      while(prev[res.i][res.j].first != p){
        res = prev[res.i][res.j].first;
      }
      command(id, prev[res.i][res.j].second);
      stepped[res.i][res.j] = true;
      return;
    } 
  }


  

bool dijkstra_dist_soldat(int id,Pos p,matrix_visitat& stepped){
    matrix_distancia dist(60,vector<int>(60,9999999));
    matrix_visitat visited(60,vector<bool>(60,false));
    dist[p.i][p.j] = 0; visited[p.i][p.j] = true;
    vector < vector< pair<Pos,Dir> > > prev(60, vector< pair<Pos,Dir> >(60));
    priority_queue < pair<int,Pos>, vector<pair<int,Pos> >, greater<pair<int,Pos>> > cua;
    cua.push(make_pair(0,p));
    bool trobat = false;
    Pos res;
    while(not cua.empty() and not trobat){
      Pos act = cua.top().second; cua.pop();
      if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Warrior and unit(cell(act).id).player != me() and soldat_a_vista(act) and not stepped[act.i][act.j]) {
        res = act;
        trobat = true;
      }
        bool first_step = true;
        for(int i = 0; i < 8; ++i){
          if(first_step){
            Pos voltant = act + Dir(i);
          if(pos_ok(voltant) and cell(voltant).type != Desert and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall and 
          cell(voltant).type != Station and eatable(voltant) and (cell(voltant).id == -1 or  (unit(cell(voltant).id).type != Car and unit(cell(voltant).id).player != me()) ) and not stepped[voltant.i][voltant.j] and
          not visited[voltant.i][voltant.j]){
            if(dist[voltant.i][voltant.j] > dist[act.i][act.j] + 1){
              dist[voltant.i][voltant.j] = dist[act.i][act.j] + 1;
              visited[voltant.i][voltant.j] = true;
              prev[voltant.i][voltant.j].first = act;
              prev[voltant.i][voltant.j].second = Dir(i);
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
            }
          }
          if(pos_ok(voltant) and cell(voltant).type != Road and cell(voltant).type != City and cell(voltant).type != Water and cell(voltant).type != Wall 
          and cell(voltant).type != Station and eatable(voltant) and (cell(voltant).id == -1 or (unit(cell(voltant).id).type != Car and unit(cell(voltant).id).player != me())) and not stepped[voltant.i][voltant.j]
          and not visited[voltant.i][voltant.j]){
            if(dist[voltant.i][voltant.j] > dist[act.i][act.j] + 4){
              dist[voltant.i][voltant.j] = dist[act.i][act.j] + 4;
              visited[voltant.i][voltant.j] = true;
              prev[voltant.i][voltant.j].first = act;
              prev[voltant.i][voltant.j].second = Dir(i);
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
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
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
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
              cua.push(make_pair(dist[voltant.i][voltant.j],voltant));
            }
          } 
          }   
          if(i == 7 ) first_step = false;     
        }
    
    }
    if(trobat){
      while(prev[res.i][res.j].first != p){
        res = prev[res.i][res.j].first;
      }
      command(id, prev[res.i][res.j].second);
      stepped[res.i][res.j] = true;
      return true;
    }
    return false; 
  }


 Dir direccio(const matrix_posicio& m, Pos destinacio, Pos inici){
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


 
 //mirem si en la carretera hi ha algun soldat enemic
 Pos bfs_xocar_soldat_brutal(Pos p, matrix_posicio& m, matrix_visitat& stepped){
    queue <Pos> aux;
    Pos res = p;
    matrix_visitat visited(60,vector <bool>(60,false));
    aux.push(p);
    bool trobat = false; visited[p.i][p.j] = true;
    while(not aux.empty()){
      Pos act = aux.front(); aux.pop();
      //mirem si trobem un soldat enemic
      if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Warrior and unit(cell(act).id).player != me() and eatable(act) and not stepped[act.i][act.j]){
        return act;
      }
      else{
        //només busquem per horitzontal i
        for(int i = 0; i < 8 and not trobat; ++i){
          Pos voltant;
          voltant = act+Dir(i);
          // si es posicio valida i no es ni aigua ni paret ni cotxe
          if(pos_ok(voltant) and cell(voltant).id != -1 and unit(cell(voltant).id).type == Warrior and unit(cell(voltant).id).player != me()){
            return act;
          } else{
            if(pos_ok(voltant) and not visited[voltant.i][voltant.j] and not stepped[voltant.i][voltant.j] and (cell(voltant).id == -1 or unit(cell(voltant).id).type != Car ) and cell(voltant).type != Desert and cell(voltant).type != Water and cell(voltant).type != City and cell(voltant).type != Station){
              m[voltant.i][voltant.j] = act;
              aux.push(voltant);
              visited[voltant.i][voltant.j] = true;
            }
          }
        }
      }
    }
    return res;
 }

 //radar de 4*4, si no troba retorna la seva posició inicial q està
 Pos radar_soldat(Pos p, matrix_posicio& m){
    queue <pair<Pos,int>> cua;
    cua.push(make_pair(p,0));
    matrix_visitat visited(60,vector <bool>(60,false));
    bool trobat = false;
    Pos res = p; visited[p.i][p.j] = true;
    while(not cua.empty() and cua.front().second <= 8 and not trobat){
      Pos aux = cua.front().first; int dd = cua.front().second + 1; cua.pop();
      if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me() and cell(aux).type != City){
        trobat = true;
        res = aux;
      }
      else{
        for(int i = 0; i < 8; ++i){
          Pos act  = aux + Dir(i);
          if(pos_ok(act) and not visited[act.i][act.j] and cell(act).type != Wall and cell(act).type != Water and cell(act).type != City){
            cua.push(make_pair(act,dd));
            m[act.i][act.j] = aux;
            visited[act.i][act.j] = true;
          }
        }
      }
    }
    return res;
}


  bool adja1(Pos p){
    for(int i = 0; i < 8; ++i){
      if(pos_ok(p+Dir(i)) and cell(p+Dir(i)).type == Road){
          return true;
      }
    }
    return false;
  }


bool radar_cotxe(Pos p){
  queue < pair<Pos,int>> cua;
  matrix_visitat visited(60,vector <bool>(60,false));
  cua.push(make_pair(p,0));
  visited[p.i][p.j] = true;
  while(not cua.empty() and cua.front().second <= 4){
    Pos act = cua.front().first; int dd = cua.front().second + 1; cua.pop();
    if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Car and unit(cell(act).id).player != me() and cell(act).type == Road and unit(cell(act).id).food > 4) return true;
    else if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Car and unit(cell(act).id).player != me() and cell(act).type == Desert and adja1(act)) return true;
    else if(pos_ok(act) and cell(act).id != -1 and unit(cell(act).id).type == Car and unit(cell(act).id).player != me() and cell(act).type == Desert and dd-1 <= 1) return true;
    for(int i = 0; i < 8; ++i){
      Pos voltant = act + Dir(i);
      if(pos_ok(voltant) and not visited[voltant.i][voltant.j] and (cell(voltant).type == Desert or cell(voltant).type == Road)){
        visited[voltant.i][voltant.j] = true;
        cua.push(make_pair(voltant,dd));
      }
    } 
  }
  return false;
}
// si la posicio no es segura return true, segura retorna false
bool fck_cotxe(Pos p){
	if( cell(p).type == Road or (cell(p).type == Desert and adja1(p))){
		if(radar_cotxe(p)) return true;
	}
  for(int i = 0; i < 8; ++i){
    Pos p1 = p + Dir(i);
    if(pos_ok(p1) and cell(p1).id != -1 and unit(cell(p1).id).type == Car and unit(cell(p1).id).player != me()) return true;
  }
  return false;
}


 //trobar la gasolinera més aprop des d'una carretera


  //funciona
 Pos bfs_buscar_carrer(matrix_posicio& m, Pos p, matrix_visitat & stepped){
    matrix_visitat visited(60, vector<bool>(60,false));
    queue <Pos> cua_no_visitat;
    Pos inicial = p;
    cua_no_visitat.push(inicial);
    visited[p.i][p.j] = true; 
    while(not cua_no_visitat.empty()){
      Pos aux = cua_no_visitat.front(); cua_no_visitat.pop();
      if(pos_ok(aux) and cell(aux).type == Road and not stepped[aux.i][aux.j]) return aux;
      for(int i = 0; i < 8; ++i){
        Pos voltant = aux + Dir(i);
        if(pos_ok(voltant) and cell(voltant).type != Wall and cell(voltant).type != Water and not stepped[voltant.i][voltant.j] and cell(voltant).type != City and not visited[voltant.i][voltant.j] and (cell(voltant).id == -1 or unit(cell(voltant).id).type != Car)){
          visited[voltant.i][voltant.j] = true;
          m[voltant.i][voltant.j] = aux;
          cua_no_visitat.push(voltant);
        }
      }
    }
    return p;
  } 
  //busca la ciutat més proxima q no es meva, evitant a mi mateix, aigua i paret
  
  //funciona que no sigui la mateixa

  Pos cotxe_ciutat_mes_proxim(matrix_posicio& m, Pos p, vector <bool> & vigilat, matrix_visitat& stepped){
    matrix_visitat visited(60, vector<bool>(60,false));
    queue <Pos> cua_no_visitat;
    Pos inicial = p;
    cua_no_visitat.push(inicial);
    visited[p.i][p.j] = true; 
    while(not cua_no_visitat.empty()){
      Pos aux = cua_no_visitat.front(); cua_no_visitat.pop();
      if(pos_ok(aux)){
        for(int i = 0; i < 8 ; ++i){
          Pos aux1 = aux + Dir(i);

          if(pos_ok(aux1)){
            if(i == 0){
              Pos aux2 = aux1 + Dir(0);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]){
                vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                return aux;
              }
            }
            else if(i == 1){
              for(int j = 0; j < 3 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                  vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
            }
            else if(i == 2){
              Pos aux2 = aux1 + Dir(2);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                return aux;}
            }
            else if(i == 3){
              for(int j = 2; j < 5 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                  vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
            }
            else if(i == 4){
              Pos aux2 = aux1 + Dir(4);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                return aux;}
            }
            else if(i == 5){
              for(int j = 4; j < 7 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                  vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
            }
            else if(i == 6){
              Pos aux2 = aux1 + Dir(6);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                return aux;}
            }
            else if(i == 7){
              for(int j = 6; j < 8 ; ++j){
                Pos aux2 = aux1 + Dir(j);
                if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                 vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
                  return aux;}
              }
              Pos aux2 = aux1 + Dir(0);
              if(pos_ok(aux2) and cell(aux2).type == City and cell(aux2).owner != me() and not vigilat[ciutat_matriu[aux2.i][aux2.j]] and not stepped[aux2.i][aux2.j]) {
                vigilat[ciutat_matriu[aux2.i][aux2.j]] = true;
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
          cua_no_visitat.push(voltant);
        }
      }
    }
    return p;
  }
  //compta els soldats de cada jugador d'una ciutat on té posició p, en principi tots tenen 0
  void i_move_car(int id, Pos p, matrix_visitat& stepped, matrix_posicio& m, vector <bool>& vigilat){

        for(int j = 0; j < 8; ++j){
          Pos aux = p + Dir(j);
          if(pos_ok(aux) and cell(aux).id != -1 and (cell(aux).type == Road or cell(aux).type == Desert) and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me() and eatable(aux) and not stepped[aux.i][aux.j]){
            command(id,Dir(j)); stepped[aux.i][aux.j] = true; return;
          }
        }  
          if(unit(id).food <= 30){
            dijkstra_dist_gas(id,p,stepped);         
          }
          else{
              if(not dijkstra_dist_soldat(id,p,stepped)){
                Pos res = cotxe_ciutat_mes_proxim(m,p,vigilat,stepped);
                if(res != p){
                  Dir d = direccio(m,res,p);
                  command(id,d);
                  Pos aux1 = p + d; stepped[aux1.i][aux1.j] = true;
                }
              } 
          }
        }
      
  
  void move_car(matrix_visitat & stepped){
    vector<int> C = cars(me());
    matrix_posicio m(60,vector<Pos>(60));
    vector <bool> vigilat(8,false);
    for(int id : C){
      if(can_move(id)){
        Pos p = unit(id).pos;
        i_move_car(id,p,stepped,m,vigilat);
      } 
      else stepped[unit(id).pos.i][unit(id).pos.j] = true; 
    }  
  }
   
  /*Aquesta funció diria que ja està bé */  
  void bfs_aigua(matrix_distancia& m, Pos inicial){
    matrix_visitat visited(60, vector<bool>(60,false));
    queue < pair<Pos,int> > cua_no_visitat;
    cua_no_visitat.push(make_pair(inicial,0));
    visited[inicial.i][inicial.j] = true; m[inicial.i][inicial.j] = 0;
    while(not cua_no_visitat.empty()){
      Pos aux = cua_no_visitat.front().first; int dd = cua_no_visitat.front().second + 1; cua_no_visitat.pop();
      for(int i = 0; i < 8; ++i){
        Pos voltant = aux + Dir(i);
        if(pos_ok(voltant) and cell(voltant).type != Wall and cell(voltant).type != Station and not visited[voltant.i][voltant.j]){
          visited[voltant.i][voltant.j] = true;
          if(m[voltant.i][voltant.j] > dd){
            m[voltant.i][voltant.j] = dd;
            cua_no_visitat.push(make_pair(voltant,dd));
          }
        }
      }
    }
  }
  void bfs_ciutat(matrix_distancia& m, Pos inicial){
    matrix_visitat visited(60, vector<bool>(60,false));
    queue < pair<Pos,int> > cua_no_visitat;
    cua_no_visitat.push(make_pair(inicial,0));
    visited[inicial.i][inicial.j] = true; m[inicial.i][inicial.j] = 0;
    while(not cua_no_visitat.empty()){
      Pos aux = cua_no_visitat.front().first; int dd = cua_no_visitat.front().second + 1; cua_no_visitat.pop();
      for(int i = 0; i < 8; ++i){
        Pos voltant = aux + Dir(i);
        if(pos_ok(voltant) and cell(voltant).type != Wall and cell(voltant).type != Water and cell(voltant).type != Station and not visited[voltant.i][voltant.j]){
          visited[voltant.i][voltant.j] = true;
          if(m[voltant.i][voltant.j] > dd){
            m[voltant.i][voltant.j] = dd;
            cua_no_visitat.push(make_pair(voltant,dd));
          }
        }
      }
    }
  }  
 




  //comences des d'una posició vàlida i busques, associo a cada ciutat un id de 0  -- 7 
  //funciona  
  void iniciar_ciutat(V_CITY& cities, matrix_visitat& m_citi, matrix_distancia& ciutat_matriu, int id, Pos p){
    if(not pos_ok(p) or cell(p).type != City or m_citi[p.i][p.j]) return;
    m_citi[p.i][p.j] = true;
    cities[id].push_back(p);
    ciutat_matriu[p.i][p.j] = id;
    for(int i = 0; i < 8; ++i) iniciar_ciutat(cities,m_citi,ciutat_matriu, id, p + Dir(i));
  }
  
  //Post: en jugadors obtenim la informació de cada ciutat 8*4 
  // també funciona 
  void comptar_soldats(vector <vector<int> >& jugadors, V_CITY& c){
    for(int i = 0; i < 8; ++i){
      for(auto w : c[i]){
        // si hi ha algun puto jugador
        if(cell(w).id != -1){
          int p = unit(cell(w).id).player;
          ++ jugadors[i][p];
        }
      }
    }
  }

  //Tactica guarra 1: quedarse dintre de la ciutat fins q no hi hagi aigua 
  //Tactica guarra 2: quan està en desert anar cap a la ciutat més propera, no atacar a ningú
  //Tactica guarra 3: dintre de la ciutat esquivar els q tenen més food q tu
  //Tactica guarra 4: distancia + 4 huajajaja anar a buscar aigua  (ok)
  //Tactica guarra 5: Mentres tant moure com es vulgui
  bool pos_safe_guerrer(Pos p){
    for(int i = 0; i < 8; ++i){
      Pos aux = p + Dir(i);
      if(pos_ok(aux) and cell(aux).id != -1 and cell(aux).type == City and unit(cell(aux).id).player != me() ) return false;
    }
    return true;
  }

  bool ciutat_enemic(int ciutat, int id, Pos p, matrix_distancia& m,matrix_visitat& stepped,vector <vector <int> >& jugadors){
    if(m[p.i][p.j] > 9) return false;
    //només procedim si veiem q la ciutat no es nostra i q no hi ha més de 2 soldats enemics
    for(int i = 0; i < 4; ++i){
      if(i != me()){
        if(cell(cities[ciutat][0]).owner == me()) return false;
        else if(jugadors[ciutat][i] > 2 and jugadors[ciutat][i]+1 < jugadors[ciutat][me()]) return false;
      }
    }
         
    for(int i = 0; i < 8; ++i){
      Pos aux = p +Dir(i);
      if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
        if(not fck_cotxe(p)){
          command(id, Dir(i));
          return true;
        }
      }
    }
         for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and m[aux.i][aux.j] < m[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true; ++jugadors[ciutat][me()];
              return true;
            }
          }
               
            for(int j = 0; j < 9; ++j){
              Pos aux = p + Dir(j);
              if(pos_ok(aux) and m[aux.i][aux.j] == m[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
                command(id,Dir(j));
                stepped[aux.i][aux.j] = true; ++jugadors[ciutat][me()];
                return true;
              }
            }
            
              for(int j = 0; j < 9; ++j){
                Pos aux = p + Dir(j);
                if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
                  command(id,Dir(j));
                  stepped[aux.i][aux.j] = true; ++jugadors[ciutat][me()];
                  return true;
                }
              }
              
              for(int j = 0; j < 9; ++j){
            Pos aux = p + Dir(j);
            if(pos_ok(aux) and m[aux.i][aux.j] < m[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car))  and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true; ++jugadors[ciutat][me()];
              return true;
            }
          }
               
            for(int j = 0; j < 9; ++j){
              Pos aux = p + Dir(j);
              if(pos_ok(aux) and m[aux.i][aux.j] == m[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not stepped[aux.i][aux.j]){
                command(id,Dir(j));
                stepped[aux.i][aux.j] = true; ++jugadors[ciutat][me()];
                return true;
              }
            }
            
              for(int j = 0; j < 9; ++j){
                Pos aux = p + Dir(j);
                if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and  not stepped[aux.i][aux.j]){
                  command(id,Dir(j));
                  stepped[aux.i][aux.j] = true; ++jugadors[ciutat][me()];
                  return true;
                }
              }
             command(id, None);  
             stepped[p.i][p.j] = true; ++jugadors[ciutat][me()];
             return true;    
  }

  void i_move_warriors(int id, Pos p, matrix_visitat& stepped,vector <vector<int> >& jugadors,vector <bool>& ciutat_enviat){

    
    if(unit(id).water <= 15 or unit(id).water <= aigua[p.i][p.j]+3){
        
        for(int i = 0; i < 8; ++i){
          Pos aux = p +Dir(i);
          if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
            if(not fck_cotxe(p)){
              command(id, Dir(i));
              return;
            }
          }
        }

        for(int j = 0; j < 8; ++j){
          Pos aux = p + Dir(j);
          if(pos_ok(aux) and aigua[aux.i][aux.j] < aigua[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
            command(id,Dir(j));
            stepped[aux.i][aux.j] = true;
            return;
          }
        }
      
        for(int j = 0; j < 9; ++j){
          Pos aux = p + Dir(j);
          if(pos_ok(aux) and aigua[aux.i][aux.j] == aigua[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
            command(id,Dir(j));
            stepped[aux.i][aux.j] = true;
            return;
          }
        }
         
        for(int j = 0; j < 9; ++j){
           Pos aux = p + Dir(j);
           if(pos_ok(aux) and aigua[aux.i][aux.j] < unit(id).water and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
            } 
          }
        for(int j = 0; j < 9; ++j){
           Pos aux = p + Dir(j);
           if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and  not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
              command(id,Dir(j));
              stepped[aux.i][aux.j] = true;
              return;
            } 
        }
        for(int i = 0; i < 8; ++i){
          Pos aux = p +Dir(i);
          if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
            if(not fck_cotxe(p)){
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
          //Road or Desert
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
                  if(not fck_cotxe(p)){
                    command(id, Dir(i));
                    return;
                  }
                }
              }
              
            vector < pair<int,int> > ordre(8);
            for(int i = 0; i < 8; ++i){
              ordre[i].first = c[i][p.i][p.j];
              ordre[i].second = i;
            }
            sort(ordre.begin(),ordre.end());


             bool realitzat = false;
            for(int i = 0; i < 8 and not realitzat; ++i){
              realitzat = ciutat_enemic(ordre[i].second,id,p,c[ordre[i].second],stepped,jugadors);
            }

            if(not realitzat){

              for(int i = 0; i < 8; ++i){
                Pos aux = p +Dir(i);
                if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
                  if(not fck_cotxe(p)){
                    command(id, Dir(i));
                    return;
                  }
                }
              }              
               for(int j = 0; j < 9; ++j){
                Pos aux = p + Dir(j);
                if(pos_ok(aux) and ciutat[aux.i][aux.j] < ciutat[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).type != Car and unit(cell(aux).id).player != me())) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
                  command(id,Dir(j));
                  stepped[aux.i][aux.j] = true;
                  return;
                }
              }
                    
              for(int j = 0; j < 9; ++j){
                Pos aux = p + Dir(j);
                if(pos_ok(aux) and ciutat[aux.i][aux.j] == ciutat[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
                  command(id,Dir(j));
                  stepped[aux.i][aux.j] = true;
                  return;
                }
              }
        
              for(int j = 0; j < 9; ++j){
                Pos aux = p + Dir(j);
                if(pos_ok(aux) and (cell(aux).id == -1 or (unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not fck_cotxe(aux) and not stepped[aux.i][aux.j]){
                  command(id,Dir(j));
                  stepped[aux.i][aux.j] = true;
                  return;
                }
              }
              for(int i = 0; i < 8; ++i){
                Pos aux = p +Dir(i);
                if(pos_ok(aux) and cell(aux).id != -1 and unit(cell(aux).id).type == Warrior and unit(cell(aux).id).player != me()){
                  if(not fck_cotxe(p)){
                    command(id, Dir(i));
                    return;
                  }
                }
              }              
               for(int j = 0; j < 9; ++j){
                Pos aux = p + Dir(j);
                if(pos_ok(aux) and ciutat[aux.i][aux.j] < ciutat[p.i][p.j] and (cell(aux).id == -1 or (unit(cell(aux).id).type != Car and unit(cell(aux).id).player != me())) and  not stepped[aux.i][aux.j]){
                  command(id,Dir(j));
                  stepped[aux.i][aux.j] = true;
                  return;
                }
              }
                    
              for(int j = 0; j < 9; ++j){
                Pos aux = p + Dir(j);
                if(pos_ok(aux) and ciutat[aux.i][aux.j] == ciutat[p.i][p.j] and (cell(aux).id == -1 or(unit(cell(aux).id).player != me() and unit(cell(aux).id).type != Car)) and not stepped[aux.i][aux.j]){
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
              if(pos_ok(aux) and ciutat[aux.i][aux.j] == ciutat[p.i][p.j] and (cell(aux).id == -1) and pos_safe_guerrer(aux) and not stepped[aux.i][aux.j]){
                command(id,Dir(j));
                stepped[aux.i][aux.j] = true;
                return;
              }
            }
   
            for(int j = 0; j < 9; ++j){
              Pos aux = p + Dir(j);
              if(pos_ok(aux) and ciutat[aux.i][aux.j] == ciutat[p.i][p.j] and (cell(aux).id == -1) and not stepped[aux.i][aux.j]){
                command(id,Dir(j));
                stepped[aux.i][aux.j] = true;
                return;
              }
            }
            for(int j = 0; j < 9; ++j){
              Pos aux = p + Dir(j);
              if(pos_ok(aux) and ciutat[aux.i][aux.j] == ciutat[p.i][p.j] and (cell(aux).id != -1 and unit(id).food > unit(cell(aux).id).food +5) and not stepped[aux.i][aux.j]){
                command(id,Dir(j));
                stepped[aux.i][aux.j] = true;
                return;
              }
            } 
            for(int j = 0; j < 9; ++j){
              Pos aux = p + Dir(j);
              if(pos_ok(aux) and ciutat[aux.i][aux.j] == 1 and (cell(aux).id != -1) and not stepped[aux.i][aux.j]){
                command(id,Dir(j));
                stepped[aux.i][aux.j] = true;
                return;
              }
            } 

        }
      }
  }

  void move_warriors(matrix_visitat& stepped) {
    if (round()% 4 != me()) return; 

    VE W = warriors(me());
    int n = W.size();
    VE perm = random_permutation(n);
    matrix_posicio m(60,vector<Pos>(60));
    vector < vector<int> > jugadors(8,vector<int>(4,0));
    comptar_soldats(jugadors,cities);
    vector <bool> ciutat_enviat(8,false);

    for (int i = 0; i < n; ++i) {
      int id = W[perm[i]];
      Pos p = unit(id).pos;
      i_move_warriors(id,p,stepped,jugadors,ciutat_enviat);
    }
  }
  


  void play () {
    //Inicialitzacions
    if(round() == 0){
      aigua = matrix_distancia(60,vector <int>(60,61));
      ciutat = matrix_distancia(60,vector <int>(60,61));
      matrix_visitat m_citi(60,vector <bool>(60,false));
      ciutat_matriu = matrix_distancia(60,vector <int>(60,9));
      c = vector <matrix_distancia>(8);
      c[0] = matrix_distancia(60,vector <int>(60,61));
      c[1] = matrix_distancia(60,vector <int>(60,61));
      c[2] = matrix_distancia(60,vector <int>(60,61));
      c[3] = matrix_distancia(60,vector <int>(60,61));
      c[4] = matrix_distancia(60,vector <int>(60,61));
      c[5] = matrix_distancia(60,vector <int>(60,61));
      c[6] = matrix_distancia(60,vector <int>(60,61));
      c[7] = matrix_distancia(60,vector <int>(60,61));
      dist_2_1 = dist_2_2 = vector <int>(24);
      dist_2_2[0] = -1;dist_2_2[1] = 0;dist_2_2[2] = 1;dist_2_2[3] = 1;dist_2_2[4] = 1;dist_2_2[5] = 0;dist_2_2[6] = -1;dist_2_2[7] = -1;dist_2_2[8] = -2;dist_2_2[9] = -1;dist_2_2[10] = 0;dist_2_2[11] = 1;dist_2_2[12] = 2;dist_2_2[13] = 2;dist_2_2[14] = 2;dist_2_2[15] = 2;dist_2_2[16] = 2;dist_2_2[17] = 1;dist_2_2[18] = 0;dist_2_2[19] = -1;dist_2_2[20] = -2;dist_2_2[21] = -2;dist_2_2[22] = -2;dist_2_2[23] = -2;
      dist_2_1[0] = -1;dist_2_1[1] = -1;dist_2_1[2] = -1;dist_2_1[3] = 0;dist_2_1[4] = 1;dist_2_1[5] = 1;dist_2_1[6] = 1;dist_2_1[7] = 0;dist_2_1[8] = -2;dist_2_1[9] = -2;dist_2_1[10] = -2;dist_2_1[11] = -2;dist_2_1[12] = -2;dist_2_1[13] = -1;dist_2_1[14] = 0;dist_2_1[15] = 1;dist_2_1[16] = 2;dist_2_1[17] = 2;dist_2_1[18] = 2;dist_2_1[19] = 2;dist_2_1[20] = 2;dist_2_1[21] = -1;dist_2_1[22] = 0;dist_2_1[23] = 1;
      cities = V_CITY(8);
      int id = 0;
      for(int i = 0; i < 60; ++i){
        for(int j = 0; j < 60; ++j){
          Pos p; p.i = i; p.j = j;
          if(cell(i,j).type == Water) bfs_aigua(aigua,p);
          else if(cell(i,j).type == City){
            bfs_ciutat(ciutat,p);
            if(not m_citi[i][j]){
              iniciar_ciutat(cities,m_citi,ciutat_matriu,id,p);
              ++id;
            }
          }      
        }
      }

      for(int i = 0; i < 8; ++i){
        for(Pos p : cities[i]){
          bfs_ciutat(c[i],p);
        }
      }
    }
 
   
      matrix_visitat stepped(60, vector<bool>(60,false)); // evitar que es matin entre ells
      move_warriors(stepped);
      move_car(stepped);
    
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);