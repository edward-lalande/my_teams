# my_teams

The aim of the my_teams project is to recode a server and a client like Microsoft's Teams.

To achieve this, we have implemented our protocol and the commands required (specified in the EPITECH-myTeams-Protocol(PET).txt file, which contains the commands and our protocol).

## Usage

Make sure to have the package `libuuid-devel` if not, download it with you package manager and to export the environment variable LD_LIBRARY_PATH to the ./libs/myteams/ folder.

```sh
    make
```

Then launch the `my_teams_server` on the port you want, by example:

```sh
    ./my_teams_server 4242
```

If you want to join the server with the client you need to specify de ip address and the port of the server

```sh
    ./myteams_cli 127.0.0.1 4242
```

## Co-Contributors

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/paulbardeur">
        <img src="https://avatars.githubusercontent.com/u/114899301?v=4" width=85><br>
        <sub>Paul Bardeur</sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/edward-lalande">
        <img src="https://avatars.githubusercontent.com/u/114470214?v=4" width=85><br>
        <sub>Edward Lalande</sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/timotheeplisson">
        <img src="https://avatars.githubusercontent.com/u/91876984?v=4" width=85><br>
        <sub>Timothee Plisson</sub>
      </a>
    </td>
  </tr>
</table>