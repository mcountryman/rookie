import * as React from "react";
import { useEffect, useState } from "react";
import { Card } from "@material-ui/core";
import CardContent from "@material-ui/core/CardContent";
import CardHeader from "@material-ui/core/CardHeader";
import CardActions from "@material-ui/core/CardActions";
import IconButton from "@material-ui/core/IconButton";
import SaveIcon from "@material-ui/icons/Save";
import TextField from "@material-ui/core/TextField";
import Grid from "@material-ui/core/Grid";

type Settings = { [index: string]: number };

export const CameraCard = () => {
  const [deviceId, setDeviceId] = useState(0);
  const [settings, setSettings] = useState({});

  useEffect(() => {
    loadDeviceId()
      .then(deviceId => setDeviceId(deviceId))
      .catch(ex => console.error(ex))
    ;

    loadSettings()
      .then(settings => setSettings(settings))
      .catch(ex => console.error(ex))
    ;

    return () => {
    };
  }, []);

  return (
    <>
      <Card>
        <CardHeader title="Camera"/>
        <CardContent>
          <Grid
            container
            spacing={3}
            direction="column">

            <Grid item xs={12}>
              <TextField
                id="device-id"
                type="number"
                label="Device Id"
                value={deviceId}
                onChange={(evt) => setDeviceId(Number(evt.target.value))}/>
            </Grid>
          </Grid>
        </CardContent>
        <CardActions>
          <IconButton
            onClick={() => {
              saveDeviceId(deviceId)
                .then(_ => console.log(`Saved`))
                .catch(ex => console.error(ex))
            }}>

            <SaveIcon/>
          </IconButton>
        </CardActions>
      </Card>
    </>
  );
};

async function saveDeviceId(value: number): Promise<void> {
  const res = await fetch(`/camera/id/${value}`, {method: "PATCH"});
  if (res.status != 200) {
    throw new Error(await res.json());
  }
}

async function loadDeviceId(): Promise<number> {
  const res = await fetch("/camera/id");
  if (res.status != 200) {
    throw new Error(await res.json());
  }

  return Number(await res.json());
}

async function saveSettings(settings: Settings): Promise<void> {
  const res = await fetch(
    "/camera",
    {
      body: JSON.stringify(this.settings),
      method: "PATCH",
    }
  );

  if (res.status != 200) {
    throw new Error(await res.json());
  }
}

async function loadSettings(): Promise<Settings> {
  const res = await fetch("camera");

  if (res.status != 200) {
    throw new Error(await res.json());
  }

  return await res.json() as Settings;
}