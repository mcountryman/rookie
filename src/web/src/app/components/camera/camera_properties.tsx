import * as React from "react";
import { useEffect, useState } from "react";
import { ExpansionPanel } from "@material-ui/core";
import ExpansionPanelSummary from "@material-ui/core/ExpansionPanelSummary";
import Typography from "@material-ui/core/Typography";
import ExpansionPanelDetails from "@material-ui/core/ExpansionPanelDetails";
import { CameraProperty } from "./camera_property";
import Grid from "@material-ui/core/Grid";
import ExpandMoreIcon from "@material-ui/icons/ExpandMore";

type Properties = { [index: string]: number };

interface IProps {
  addSaveHandler: (handler: () => void) => void;
}

export const CameraProperties = (props: IProps) => {
  const [properties, setProperties] = useState({});

  useEffect(() => {
    loadProperties()
      .then(properties => setProperties(properties))
      .catch(ex => console.error(ex))
    ;

    return () => {};
  }, []);

  props.addSaveHandler(() =>
    saveProperties(properties)
      .then(_ => console.log())
      .catch(ex => console.error(ex))
  );

  return (
    <Grid
      container
      spacing={3}
      direction="column"
    >
      {
        Object
          .keys(properties)
          .map(key =>
            <CameraProperty
              key={key}
              name={key}
              value={properties[key]}
              onChange={value => {
                setProperties({
                  [key]: value,
                  ...properties,
                })
              }}
            />
          )
      }
    </Grid>
  );
}

async function saveProperties(properties: Properties): Promise<void> {
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

async function loadProperties(): Promise<Properties> {
  const res = await fetch("camera");

  if (res.status != 200) {
    throw new Error(await res.json());
  }

  return await res.json() as Properties;
}