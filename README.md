# UDP-Socket-Server-and-Client-Implementation-in-Cpp

Ky është një projekt semestral i zhvilluar nga studentët e Universitetit të Prishtinës "Hasan Prishtina" – Fakulteti i Inxhinierisë Elektrike dhe Kompjuterike, në lëndën **Rrjeta Kompjuterike**, udhëhequr nga Prof. Blerim Rexha dhe PhD. Mergim Hoti.

## 📑 Tabela e Përmbajtjes
- [Përmbledhje](#përmbledhje)
- [Karakteristikat Kryesore](#🚀-karakteristikat-kryesore)
  - [Serveri](#serveri)
  - [Klienti](#klienti)
- [Udhëzime për Instalimin dhe Përdorimin](#🛠️-udhëzime-për-instalimin-dhe-përdorimin)
- [Kontributorët](#👥-kontributorët)
- [Përfundim](#përfundim)

## Përmbledhje
Ky projekt ilustron një sistem server-klient duke përdorur **UDP sockets** në C++. Serveri pret kërkesa nga klientët, përpunon mesazhet dhe ofron qasje të plotë ose të kufizuar në dosjet e ruajtura, bazuar në privilegjet e klientëve.

## 🚀 Karakteristikat Kryesore

### Serveri
- **Konfigurim i Serverit**: Caktoni IP adresën dhe portin e serverit.
- **Dëgjimi i Kërkesave**: Serveri është aktiv për të pritur kërkesa nga klientët.
- **Menaxhimi i Kërkesave**: Përpunon kërkesa për qasje në dosje dhe komandat e klientëve.
- **Qasje në Dosje**: Ofron qasje të plotë për një klient dhe qasje të kufizuar për të tjerët.

### Klienti
- **Krijimi i Socket-it**: Krijon një socket për lidhje me serverin përmes UDP.
- **Privilegjet e Klientit**: Një klient ka qasje të plotë (lexim, shkrim, fshirje), ndërsa të tjerët kanë vetëm qasje për lexim.
- **Dërgimi i Komandave**: Klientët mund të dërgojnë komanda si:
  - **LIST_FILES**: Liston dosjet në server.
  - **READ_FILE \<filename\>**: Lexon përmbajtjen e një dosje.
  - **ADD_FILE \<filename\> \<content\>**: Krijon një dosje me përmbajtjen e dhënë.
  - **EDIT_FILE \<filename\> \<content\>**: Përditëson përmbajtjen e një dosje ekzistuese.
  - **DELETE_FILE \<filename\>**: Fshin një dosje të dhënë.

## 🛠️ Udhëzime për Instalimin dhe Përdorimin

1. **Klononi Repositorin**:
   ```bash
   git clone https://github.com/adrianmehaj/UDP-Socket-Server-and-Client-Implementation-in-Cpp
   ```

2. **Konfiguroni Visual Studio 2022**:
   - Sigurohuni që të keni instaluar **Windows SDK** dhe të keni aktivizuar **Winsock library**.
   - Hapni projektin në Visual Studio dhe caktoni IP dhe portin e serverit.

3. **Ekzekutoni Serverin**:
   - Ndërtoni dhe ekzekutoni serverin

4. **Ekzekutoni Klientin**:
   - Ndërtoni dhe ekzekutoni klientin për të dërguar kërkesa


## 👥 Kontributorët

- [Adrian Mehaj](https://github.com/adrianmehaj)
- [Ag Hamiti](https://github.com/aghamiti)
- [Agnesa Hulaj](https://github.com/AgnesaHulaj2)


## Përfundim
Ky projekt ofron një shembull praktik të përdorimit të **UDP socket programming** në C++, duke treguar se si mund të krijoni një sistem të thjeshtë për qasje në dosje përmes një arkitekture server-klient.
