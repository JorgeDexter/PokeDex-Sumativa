import { Component } from '@angular/core';
import { APIServiceService } from '../Services/apiservice.service';
import { Firestore } from '@angular/fire/firestore';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  pokemonName: string = "";
  namePokemon: any;
  pokemonType: string = "";

  constructor(private api: APIServiceService, private db: Firestore) { }

  getPokemonByName() {
    this.api.getPokemonName(this.pokemonName).subscribe((data) => {
      this.namePokemon = data;
      this.getPokemonType();
    });
  }
  
  getPokemonType() {
    this.api.getPokemonByIdOrName(this.pokemonName).subscribe((data) => {
      this.pokemonType = data.types.map((typeObj: any) => typeObj.type.name).join(', ');
      this.api.savePokemonType(this.pokemonName, this.pokemonType);
    });
  }
}

