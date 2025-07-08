import { ApplicationModel } from './ApplicationModel.js';

const DB_NAME = 'MiApp';
const DB_VERSION = 1;
const STORE_NAME = 'usuarios';

async function abrirDB() {
  return new Promise((resolve, reject) => {
    const request = indexedDB.open(DB_NAME, DB_VERSION);

    request.onupgradeneeded = (event) => {
      const db = event.target.result;
      if (!db.objectStoreNames.contains(STORE_NAME)) {
        db.createObjectStore(STORE_NAME, { keyPath: 'usuario' });
      }
    };

    request.onsuccess = (event) => resolve(event.target.result);
    request.onerror = (event) => reject(event.target.error);
  });
}

async function guardarUsuariosSiNoExisten(db, usuarios) {
  return new Promise((resolve, reject) => {
    const tx = db.transaction([STORE_NAME], 'readonly');
    const store = tx.objectStore(STORE_NAME);
    const getAll = store.getAll();

    getAll.onsuccess = () => {
      if (getAll.result.length === 0) {
        const txAdd = db.transaction([STORE_NAME], 'readwrite');
        const storeAdd = txAdd.objectStore(STORE_NAME);
        usuarios.forEach(u => storeAdd.add(u));

        txAdd.oncomplete = () => resolve('Usuarios insertados en IndexedDB.');
        txAdd.onerror = (e) => reject(e);
      } else {
        resolve('Usuarios ya estaban en IndexedDB.');
      }
    };

    getAll.onerror = (e) => reject(e);
  });
}

async function obtenerUsuariosDesdeIndexedDB(db) {
  return new Promise((resolve, reject) => {
    const tx = db.transaction([STORE_NAME], 'readonly');
    const store = tx.objectStore(STORE_NAME);
    const request = store.getAll();

    request.onsuccess = () => resolve(request.result);
    request.onerror = (e) => reject(e);
  });
}

const appModel = new ApplicationModel();
const usuarios = appModel.usuarios.usuarios;

abrirDB()
  .then(db => guardarUsuariosSiNoExisten(db, usuarios)
    .then(msg => {
      console.log(msg);
      return obtenerUsuariosDesdeIndexedDB(db);
    })
    .then(data => console.log('Usuarios desde IndexedDB:', data))
  )
  .catch(console.error);
