import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Firestore, doc, DocumentData, setDoc } from '@angular/fire/firestore';

@Injectable({
  providedIn: 'root'
})
export class APIServiceService {
  
  private apiUrl = 'https://pokeapi.co/api/v2/';
  
  constructor(private http: HttpClient, private db: Firestore) { }

  getPokemonName(name: any): Observable<any> {
    return this.http.get(this.apiUrl + "pokemon/" + name);
  }
  
  getPokemonByIdOrName(idOrName: string): Observable<any> {
    return this.http.get<any>(`${this.apiUrl}pokemon/${idOrName.toLowerCase()}`);
  }

  savePokemonType(name: string, type: string): void {
    const pokemonRef = doc(this.db, 'Pokemons', 'Pokemon');
    setDoc(pokemonRef, { tipo: type })
      .then(() => {
        console.log('Tipo de Pokémon guardado correctamente en Firestore');
      })
      .catch((error: any) => {
        console.error('Error al guardar el tipo de Pokémon en Firestore:', error);
      });
  }
}
