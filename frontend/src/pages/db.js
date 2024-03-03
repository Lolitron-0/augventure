import { initializeApp } from "firebase/app";
import { getDatabase, onSnapshot } from "firebase/database";

const config = {
    apiKey: "AIzaSyB6Het2lTpoQOzwAV1IeFoun8OnmpDgZPI",
    authDomain: "augventure-1d276.firebaseapp.com",
    projectId: "augventure-1d276",
    storageBucket: "augventure-1d276.appspot.com",
    messagingSenderId: "944191102319",
    appId: "1:944191102319:web:d8d45eb420289e30b61c9a",
    measurementId: "G-Y28DEDCF8L"
}

const app = initializeApp(config);
const db = getDatabase(app);

export { db, onSnapshot };